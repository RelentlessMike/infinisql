/*
 * Copyright (c) 2013 Mark Travis <mtravis15432+src@gmail.com>
 * All rights reserved. No warranty, explicit or implicit, provided.
 *
 * This file is part of InfiniSQL (tm). It is available either under the
 * GNU Affero Public License or under a commercial license. Contact the
 * copyright holder for information about a commercial license if terms
 * of the GNU Affero Public License do not suit you.
 *
 * This copy of InfiniSQL is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * InfiniSQL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero Public License for more details.
 *
 * You should have received a copy of the GNU Affero Public License
 * along with InfiniSQL. It should be in the top level of the source
 * directory in a file entitled "COPYING".
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <sys/un.h>
#include "version.h"
#include "infinisql_gch.h"
#include "infinisql_Topology.h"
#line 31 "main.cc"

void *topologyMgr(void *);

FILE *logfile;
cfg_s cfgs;
string zmqsocket;
class Topology nodeTopology;
pthread_mutex_t nodeTopologyMutex;
void *zmqcontext;
string connectionhandlersockfile;
int connectionhandlersockfd;
string storedprocprefix = "InfiniSQL_";

int main(int argc, char **argv)
{
  zmqcontext = zmq_ctx_new();
  zmq_ctx_set(zmqcontext, ZMQ_IO_THREADS, 2);
  setlinebuf(stdout);

  string logfilename;
  int c;

  while ((c = getopt(argc, argv, "l:m:n:hp:v")) != -1)
  {
    switch (c)
    {
      case 'm':
        zmqsocket.assign("tcp://");
        zmqsocket.append(optarg, strlen(optarg));
        break;

      case 'l':
        logfilename.assign(optarg, strlen(optarg));
        break;

      case 'n':
        nodeTopology.nodeid = atol(optarg);
        break;

      case 'p':
        connectionhandlersockfile.assign(optarg, strlen(optarg));
        break;

      case 'h':
        printf("-m <management ip:port> -n <nodeid> -l <log path/file> -v\n");
        exit(0);
        break;

      case 'v':
        printf("%s\n", version);
        exit(0);

      default:
        ;
    }
  }

  if (!logfilename.size())
  {
    logfilename.assign("/tmp/infinisqld.log");
  }

  logfile = fopen(logfilename.c_str(), "a");
  printf("Initialized log file.\n");
  fprintf(logfile, "Initialized the log file in main.cc");
  fflush(logfile);

  if (logfile==NULL)
  {
    printf("%s %i cannot open logfile %s errno %i\n", __FILE__, __LINE__,
           logfilename.c_str(), errno);
    exit(1);
  }

  setlinebuf(logfile);

  /* create socket for connectionhandler. needs to be here because
   * connectionhandler doesn't start before obgw
   */

  if (!access(connectionhandlersockfile.c_str(), F_OK))
  {
    if (unlink(connectionhandlersockfile.c_str()))
    {
      printf("%s %i can't remove connectionhandlersockfile %s errno %i\n",
             __FILE__, __LINE__, connectionhandlersockfile.c_str(), errno);
      exit(1);
    }
  }

  connectionhandlersockfd = socket(AF_UNIX, SOCK_STREAM, 0);
  struct sockaddr_un sun;
  sun.sun_family = AF_UNIX;
  strncpy(sun.sun_path, connectionhandlersockfile.c_str(),
          connectionhandlersockfile.size()+1);
  //  printf("%s %i sun.sun_path '%s'\n", __FILE__, __LINE__, sun.sun_path);

  if (bind(connectionhandlersockfd, (struct sockaddr *)&sun,
           strlen(sun.sun_path)+sizeof(sun.sun_family))==-1)
  {
    printf("%s %i can't bind connectionhandlersockfile %s errno %i\n", __FILE__,
           __LINE__, connectionhandlersockfile.c_str(), errno);
    exit(1);
  }

  chmod(connectionhandlersockfile.c_str(), S_IRUSR | S_IWUSR);
  listen(connectionhandlersockfd, 1);
  /* have connectionhandler do the accept(). listen() needs to happen now so
   * obgw can connect() to it before connectionhandler is started
   */

  /*
  urandomsockfd = open("/dev/urandom", O_RDONLY);
  if (urandomsockfd == -1)
  {
    printf("%s %i can't open /dev/urandom errno %i\n", __FILE__, __LINE__,
        errno);
    exit(1);
  }
  */

  pthread_mutexattr_t attr;
  attr.__align = PTHREAD_MUTEX_ADAPTIVE_NP;
  pthread_mutex_init(&nodeTopologyMutex, &attr);
  pthread_t topologyMgrThread;
  Topology::partitionAddress *arg = new Topology::partitionAddress();
  arg->type = ACTOR_TOPOLOGYMGR;
  arg->mbox = new class Mbox;
  arg->address.nodeid = 1;
  arg->address.actorid = 1;
  arg->instance = -1;

  int rv;
  rv = pthread_create(&topologyMgrThread, NULL, topologyMgr, arg);

  if (rv)
  {
    printf("%s %i pthread_create rv %i\n", __FILE__, __LINE__, rv);
    exit(1);
  }

  while (1)
  {
    sleep(10);
  }

  return 0;
}

// global functions
void msgpack2Vector(vector<string> *resultvector, char *payload, int64_t length)
{
  msgpack::unpacked msg;
  msgpack::unpack(&msg, payload, length);
  msgpack::object obj = msg.get();
  obj.convert(resultvector);
}

void debug(char *description, int line, char *file)
{
  fprintf(logfile, "DEBUG %i %s %s\n", line, file, description);
}

char setdeleteflag(char *c)
{
  return *c |= 1 << DELETEFLAG;
}

bool getdeleteflag(char c)
{
  return c & 1 << DELETEFLAG;
}

char cleardeleteflag(char *c)
{
  return *c &= ~(1 << DELETEFLAG);
}

char setinsertflag(char *c)
{
  return *c |= 1 << INSERTFLAG;
}

bool getinsertflag(char c)
{
  return c & 1 << INSERTFLAG;
}

char clearinsertflag(char *c)
{
  return *c &= ~(1 << INSERTFLAG);
}

bool setwritelock(char *c)
{
  if (*c & 1 << LOCKEDFLAG)   // already locked
  {
    return false;
  }

  *c |= 1 << LOCKEDFLAG;
  *c |= 1 << LOCKTYPEFLAG;
  return true;
}

bool setreadlock(char *c)
{
  if (*c & 1 << LOCKEDFLAG)   // already locked
  {
    return false;
  }

  *c |= 1 << LOCKEDFLAG;
  *c &= ~(1 << LOCKTYPEFLAG);
  return true;
}

char clearlockedflag(char *c)
{
  return *c &= ~(1 << LOCKEDFLAG);
}

locktype_e getlocktype(char c)
{
  if (!(c & 1 << LOCKEDFLAG))
  {
    return NOLOCK;
  }

  if (c & 1 << LOCKTYPEFLAG)
  {
    return WRITELOCK;
  }
  else
  {
    return READLOCK;
  }
}

char clearreplacedeleteflag(char *c)
{
  return *c &= ~(1 << REPLACEDELETEFLAG);
}

bool getreplacedeleteflag(char c)
{
  return c & 1 << REPLACEDELETEFLAG;
}

char setreplacedeleteflag(char *c)
{
  return *c |= 1 << REPLACEDELETEFLAG;
}

int64_t getPartitionid(fieldValue_s &fieldVal, fieldtype_e type,
                       int64_t numpartitions)
{
  switch (type)
  {
    case INT:
      return SpookyHash::Hash64((void *) &fieldVal.value.integer,
                                sizeof(fieldVal.value.integer), 0) % numpartitions;
      break;

    case UINT:
      return SpookyHash::Hash64((void *) &fieldVal.value.uinteger,
                                sizeof(fieldVal.value.uinteger), 0) % numpartitions;
      break;

    case BOOL:
      return SpookyHash::Hash64((void *) &fieldVal.value.boolean,
                                sizeof(fieldVal.value.boolean), 0) % numpartitions;
      break;

    case FLOAT:
      return SpookyHash::Hash64((void *) &fieldVal.value.floating,
                                sizeof(fieldVal.value.floating), 0) % numpartitions;
      break;

    case CHAR:
      return SpookyHash::Hash64((void *) &fieldVal.value.character,
                                sizeof(fieldVal.value.character), 0) % numpartitions;
      break;

    case CHARX:
      return SpookyHash::Hash64((void *) fieldVal.str.c_str(),
                                fieldVal.str.length(), 0) % numpartitions;
      break;

    case VARCHAR:
      return SpookyHash::Hash64((void *) fieldVal.str.c_str(),
                                fieldVal.str.length(), 0) % numpartitions;
      break;

    default:
      printf("%s %i anomaly fieldtype %i\n", __FILE__, __LINE__, type);
      return -1;
  }
}

// no escape chars specified as yet
void like2Regex(string &likeStr)
{
  size_t pos;

  while ((pos = likeStr.find('_', 0)) != string::npos)
  {
    likeStr[pos]='.';
  }

  while ((pos = likeStr.find('%', 0)) != string::npos)
  {
    likeStr[pos]='*';
    likeStr.insert(pos, 1, '.');
  }
}

bool compareFields(fieldtype_e type, const fieldValue_s &val1,
                   const fieldValue_s &val2)
{
  if (val1.isnull==true && val2.isnull==true)
  {
    return true;
  }
  else if (val1.isnull==true || val2.isnull==true)
  {
    return false;
  }

  switch (type)
  {
    case INT:
      if (val1.value.integer==val2.value.integer)
      {
        return true;
      }

      break;

    case UINT:
      if (val1.value.uinteger==val2.value.uinteger)
      {
        return true;
      }

      break;

    case BOOL:
      if (val1.value.boolean==val2.value.boolean)
      {
        return true;
      }

      break;

    case FLOAT:
      if (val1.value.floating==val2.value.floating)
      {
        return true;
      }

      break;

    case CHAR:
      if (val1.value.character==val2.value.character)
      {
        return true;
      }

      break;

    case CHARX:
      if (val1.str.compare(val2.str)==0)
      {
        return true;
      }

      break;

    case VARCHAR:
      if (val1.str.compare(val2.str)==0)
      {
        return true;
      }

      break;

    default:
      printf("%s %i anomaly %i\n", __FILE__, __LINE__, type);
  }

  return false;
}

void trimspace(string &input)
{
  size_t last=input.find_last_not_of(' ');

  if (last != string::npos)
  {
    input.erase(last+1);
  }
  else
  {
    input.clear();
  }
}

void stagedRow2ReturnRow(const stagedRow_s &stagedRow, returnRow_s &returnRow)
{
  returnRow.previoussubtransactionid=stagedRow.previoussubtransactionid;
  returnRow.locktype=stagedRow.locktype;

  switch (stagedRow.cmd)
  {
    case NOCOMMAND:
      returnRow.rowid=stagedRow.originalrowid;
      returnRow.row=stagedRow.originalRow;
      break;

    case INSERT:
      returnRow.rowid=stagedRow.newrowid;
      returnRow.row=stagedRow.newRow;
      break;

    case UPDATE:
      returnRow.rowid=stagedRow.newrowid;
      returnRow.row=stagedRow.newRow;
      break;

    default:
      printf("%s %i anomaly %i\n", __FILE__, __LINE__, stagedRow.cmd);
      returnRow=returnRow_s();
  }
}

void logDebugMessage(char debugLogFilename[DBG_LOG_FILENAME_SIZE], int lineNumber, char debugLogMessage[DBG_LOG_MSG_SIZE], const char *exceptionText)
{
  fprintf(logfile, "DEBUG:\t%s %i %s %i %s %s\n", debugLogFilename, lineNumber, __DATE__, __TIME__, debugLogMessage, exceptionText);
  fflush(logfile);
}

void logDebugMessage(char debugLogFilename[DBG_LOG_FILENAME_SIZE], int lineNumber, char debugLogMessage[DBG_LOG_MSG_SIZE])
{
  fprintf(logfile, "DEBUG:\t%s %i %s %i %s\n", debugLogFilename, lineNumber, __DATE__, __TIME__, debugLogMessage);
  fflush(logfile);
}

/** @mainpage Yo
 * =====================
 * This is the main page for InfiniSQL
 * ------------------------
 * with some headings and whatnot
 * ============================
 *
 * Foo baz
 */
