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

#ifndef DEFS_HPP
#define DEFS_HPP

// Miscellaneous constants (initially added by JLH)
#define NO_EVENTS 0
#define INVALID -1
#define NO_DIFFERENCES 0
#define NO_EVENTS 0
#define LOG_MSG_SIZE 256			// max size of message to pass to logMessage()
#define DBG_LOG_FILENAME_SIZE 256		// max size of filename to pass to logDebugMessage()
#define DBG_LOG_MSG_SIZE 256			// max size of message to pass to logDebugMessage()
#define MESSAGE_LENGTH_NUMBER_OF_BYTES 8	// how many bytes are used to store the message length

// Error constants (initially added by JLH)
#define E_CAUGHT_EXCEPTION 1

// Wait time constants
#define DO_NOT_WAIT 0
#define ZERO_MICROSECONDS 0
#define ONE_HUNDRED_MICROSECONDS 100
#define WAIT_FOREVER -1
#define MICROSECOND_MULTIPLIER 1000

#define APISTATUS_OK 0
#define APISTATUS_NOTOK 1
#define APISTATUS_NULLCONSTRAINT 2
#define APISTATUS_PENDING 3
#define APISTATUS_FIELD 4
#define APISTATUS_STATE 5
#define APISTATUS_UNIQUECONSTRAINT 6
#define APISTATUS_FOUND 7
#define APISTATUS_DEADLOCK 8
#define APISTATUS_LOCK 9

// types of MBOXES (for label argument to mbox_create), but probably
// actually doesn't matter
#define MBOXCONNECTIONHANDLER 1
#define MBOXTRANSACTIONAGENT 2
#define MBOXENGINE 3

// message topics
#define TOPICMBOXES 1
#define TOPICEPOLLEVENT 2

// TransactionAgent <-> UserSchemaMgr
#define TOPICLOGIN 3
#define TOPICLOGINOK 4
#define TOPICLOGINFAIL 5
#define TOPICCHANGEPASSWORD 6
#define TOPICCHANGEPASSWORDOK 7
#define TOPICCHANGEPASSWORDFAIL 8
#define TOPICCREATEDOMAIN 9
#define TOPICCREATEDOMAINOK 10
#define TOPICCREATEDOMAINFAIL 11
#define TOPICCREATEUSER 12
#define TOPICCREATEUSEROK 13
#define TOPICCREATEUSERFAIL 14
#define TOPICDELETEUSER 15
#define TOPICDELETEUSEROK 16
#define TOPICDELETEUSERFAIL 17
#define TOPICDELETEDOMAIN 18
#define TOPICDELETEDOMAINOK 19
#define TOPICDELETEDOMAINFAIL 20
#define TOPICSCHEMAREQUEST 21
#define TOPICSCHEMAREPLY 22
#define TOPICDEADLOCKNEW 23
#define TOPICDEADLOCKCHANGE 24
#define TOPICDEADLOCKREMOVE 25
#define TOPICLOADPROCEDURE 26
#define TOPICTRANSACTION 27
#define TOPICDISPATCH 28
#define TOPICDISPATCHED 29
#define TOPICDEADLOCKABORT 30
#define TOPICENDSUBTRANSACTION 31
#define TOPICTOPOLOGY

// statuses to client
#define STATUS_OK 0
#define STATUS_NOTOK 1

// statuses builtins
#define BUILTIN_STATUS_OK 0
#define BUILTIN_STATUS_NOTOK 1

#define PAYLOADSIZE 128

enum listenertype_e
{
  LISTENER_NONE = 0,
  LISTENER_RAW,			// used by login, createtable and other builtins
  LISTENER_PG			// Postgres wire protocol handler
};

// to builtins
enum builtincmds_e
{
  NOCMD = 0,
  STARTCMD,
  OKCMD,
  NOTOKCMD,
  USMRESPONSECMD,
  TASENGINESRESPONSECMD,
  ABORTCMD
};

enum indextype_e
{
  NONE = 0,
  UNIQUE = 1,
  NONUNIQUE = 2,
  UNORDERED = 3,
  UNIQUENOTNULL = 4,
  NONUNIQUENOTNULL = 5,
  UNORDEREDNOTNULL = 6
};

enum indexmaptype_e
{
  uniqueint = 0,
  nonuniqueint = 1,
  unorderedint = 2,
  uniqueuint = 3,
  nonuniqueuint = 4,
  unordereduint = 5,
  uniquebool = 6,
  nonuniquebool = 7,
  unorderedbool = 8,
  uniquefloat = 9,
  nonuniquefloat = 10,
  unorderedfloat = 11,
  uniquechar = 12,
  nonuniquechar = 13,
  unorderedchar = 14,
  uniquecharx = 15,
  nonuniquecharx = 16,
  unorderedcharx = 17,
  uniquevarchar = 18,
  nonuniquevarchar = 19,
  unorderedvarchar = 20
};

enum maptype_e
{
  Unique = 0,
  Nonunique = 1,
  Unordered = 2
};

enum topic_e
{
  TOPIC_NONE = 0,
  TOPIC_MBOXES = 1,
  TOPIC_SOCKET = 2,				// for messages that contain a socket that needs to be read from
  TOPIC_LOGIN = 3,
  TOPIC_LOGINOK = 4,
  TOPIC_LOGINFAIL = 5,
  TOPIC_CHANGEPASSWORD = 6,
  TOPIC_CHANGEPASSWORDOK = 7,
  TOPIC_CHANGEPASSWORDFAIL = 8,
  TOPIC_CREATEDOMAIN = 9,
  TOPIC_CREATEDOMAINOK = 10,
  TOPIC_CREATEDOMAINFAIL = 11,
  TOPIC_CREATEUSER = 12,
  TOPIC_CREATEUSEROK = 13,
  TOPIC_CREATEUSERFAIL = 14,
  TOPIC_DELETEUSER = 15,
  TOPIC_DELETEUSEROK = 16,
  TOPIC_DELETEUSERFAIL = 17,
  TOPIC_DELETEDOMAIN = 18,
  TOPIC_DELETEDOMAINOK = 19,
  TOPIC_DELETEDOMAINFAIL = 20,
  TOPIC_SCHEMAREQUEST = 21,
  TOPIC_SCHEMAREPLY = 22,
  TOPIC_DEADLOCKNEW = 23,
  TOPIC_DEADLOCKCHANGE = 24,
  TOPIC_DEADLOCKREMOVE = 25,
  TOPIC_LOADPROCEDURE = 26,
  TOPIC_TRANSACTION = 27,
  TOPIC_DISPATCH = 28,
  TOPIC_ACKDISPATCH = 29,
  TOPIC_DEADLOCKABORT = 30,
  TOPIC_ENDSUBTRANSACTION = 31,
  TOPIC_PROFILE = 32,				// deprecated
  TOPIC_TOPOLOGY = 33,
  TOPIC_NEWPROCEDURE = 34,
  TOPIC_PROCEDURE1 = 35,
  TOPIC_PROCEDURE2 = 36,
  TOPIC_APPLY = 37,
  TOPIC_ACKAPPLY = 38,
  TOPIC_CLOSESOCKET = 40,
  TOPIC_OPERATION = 41,
  TOPIC_COMPILE = 42,
  TOPIC_TABLENAME = 43,
  TOPIC_FIELDNAME = 44
};

enum payloadtype_e
{
  PAYLOADNONE = 0,
  PAYLOADMESSAGE,
  PAYLOADSOCKET,
  PAYLOADUSERSCHEMA,
  PAYLOADDEADLOCK,
  PAYLOADSUBTRANSACTION,
  PAYLOADCOMMITROLLBACK,
  PAYLOADDISPATCH,
  PAYLOADACKDISPATCH,
  PAYLOADAPPLY,
  PAYLOADACKAPPLY
};

enum operationtype_e
{
  OPERATION_NONE = 0,
  OPERATION_LOGIN
};

enum operatortypes_e
{
  OPERATOR_NONE = 0,
  OPERATOR_CONCATENATION = 1,
  OPERATOR_ADDITION = 2,
  OPERATOR_SUBTRACTION = 3,
  OPERATOR_MULTIPLICATION = 4,
  OPERATOR_DIVISION = 5,
  OPERATOR_NEGATION = 7,
  OPERATOR_AND = 8,
  OPERATOR_OR = 9,
  OPERATOR_NOT = 10,
  OPERATOR_TRUE = 11,
  OPERATOR_FALSE = 12,
  OPERATOR_UNKNOWN = 13,
  OPERATOR_EQ = 14,
  OPERATOR_NE = 15,
  OPERATOR_LT = 16,
  OPERATOR_GT = 17,
  OPERATOR_LTE = 18,
  OPERATOR_GTE = 19,
  OPERATOR_BETWEEN = 20,
  OPERATOR_ISNULL = 21,
  OPERATOR_IN = 22,
  OPERATOR_LIKE = 23,
  OPERATOR_EXISTS = 24,
  OPERATOR_UNIQUE = 25,
  OPERATOR_BETWEENAND = 26,
  OPERATOR_NOTBETWEEN = 27,
  OPERATOR_ISNOTNULL = 28,
  OPERATOR_NOTIN = 29,
  OPERATOR_NOTLIKE = 30,
  OPERATOR_REGEX = 31,
  OPERATOR_SELECTALL = 32,
  OPERATOR_NULL = 33
};

#define OPERAND_STRING  'a'
#define OPERAND_IDENTIFIER  'b'
#define OPERAND_PARAMETER   'c'
#define OPERAND_SUBQUERY    'd'
#define OPERAND_INTEGER 'e'
#define OPERAND_FLOAT    'f'
#define OPERAND_AGGREGATE   'g'
#define OPERAND_FIELDID 'h'
#define OPERAND_NULL 'i'
#define OPERAND_PREDICATERESULTS    'j'
#define OPERAND_SUBQUERYRESULTS 'k'
#define OPERAND_BOOLEAN 'l'

#define AGGREGATE_AVG   'a'
#define AGGREGATE_COUNT 'b'
#define AGGREGATE_MAX   'c'
#define AGGREGATE_MIN   'd'
#define AGGREGATE_SUM   'e'

// passing messages pertaining to specific builtins
#define BUILTINCREATESCHEMA 3
#define BUILTINCREATETABLE 4
#define BUILTINADDCOLUMN 5
#define BUILTINDELETEINDEX 6
#define BUILTINDELETETABLE 7
#define BUILTINDELETESCHEMA 8
#define BUILTINDUMPCONFIG 9

// states
#define ST_USM 1 // waiting for user schema manager
#define ST_TASENGINES 2 // waiting for tas and engines to reply

// operation type
#define OP_AUTH 1
#define OP_SCHEMA 2
#define OP_PGLOGIN 3

// namespaces & usings
using namespace std;
using namespace CryptoPP;
using namespace msgpack;
using std::string;
using std::vector;
using std::map;
using std::multimap;
using msgpack::sbuffer;
using boost::lexical_cast;

// enums
enum fieldtype_e
{
  INT = 0,
  UINT = 1,
  BOOL = 2,
  FLOAT = 3,
  CHAR = 4,
  CHARX = 5,
  VARCHAR = 6
};

enum enginecmds_e
{
  newrow
};

enum locktype_e
{
  NOTFOUNDLOCK = -1,
  NOLOCK = 0,
  READLOCK,
  WRITELOCK,
  PENDINGLOCK,
  INDEXLOCK,
  INDEXPENDINGLOCK,
  PENDINGTOWRITELOCK,
  PENDINGTOREADLOCK,
  PENDINGTONOLOCK,
  PENDINGTOINDEXLOCK,
  PENDINGTOINDEXNOLOCK
};

enum pendingprimitive_e
{
  NOCOMMAND = 0,
  INSERT,
  UPDATE,
  DELETE,
  REPLACE,
  SELECT,
  FETCH,
  UNLOCK,
  COMMIT,
  ROLLBACK,
  PRIMITIVE_SQLPREDICATE,
  PRIMITIVE_SQLSELECTALL,
  PRIMITIVE_SQLSELECTALLFORDELETE,
  PRIMITIVE_SQLSELECTALLFORUPDATE,
  PRIMITIVE_SQLDELETE,
  PRIMITIVE_SQLINSERT,
  PRIMITIVE_SQLUPDATE,
  PRIMITIVE_SQLREPLACE
};

// should merge this with pendingprimitive probably
enum cmd_e
{
  CMD_NONE = 0,
  CMD_SELECT,
  CMD_INSERT,
  CMD_UPDATE,
  CMD_DELETE,
  CMD_BEGIN,
  CMD_COMMIT,
  CMD_ROLLBACK,
  CMD_SET,
  CMD_STOREDPROCEDURE
};

enum enginecmd_e
{
  NOENGINECMD = 0,
  NEWROW,
  UNIQUEINDEX,
  UPDATEROW,
  DELETEROW,
  REPLACEDELETEROW,
  INDEXSEARCH,
  SELECTROWS,
  COMMITCMD,
  ROLLBACKCMD,
  REVERTCMD,
  UNLOCKCMD,
  SEARCHRETURN1
};

/** Global configs */
typedef struct
{
  int anonymousping;
  int badloginmessages;
} cfg_s;
extern cfg_s cfgs;

extern FILE *logfile;
extern string zmqsocket;
extern void *zmqcontext;
extern string connectionhandlersockfile;
extern int connectionhandlersockfd;
extern string storedprocprefix;

typedef struct
{
  fieldtype_e type;
  string name;
} fieldtypename_s;

typedef struct
{
  uint64_t instance;
  class Mbox *mbox;
  int epollfd;
} serventIdentity_s;

typedef struct
{
  void *procedurecreator; //typedef ApiInterface*(*spclasscreate)(void);
  void *proceduredestroyer; //typedef void(*spclassdestroy)(ApiInterface*);
} procedures_s;

typedef struct
{
  boost::unordered_set<string> locked;
  boost::unordered_set<string> waiting;
} newDeadLockLists_s;

typedef struct
{
  int64_t rowid;
  int64_t previoussubtransactionid;
  locktype_e locktype;
  string row;
} returnRow_s;

typedef union fieldInput_u
{
  int64_t integer;
  uint64_t uinteger;
  bool boolean;
  long double floating;
  char character;
} fieldInput_s;

typedef struct
{
  fieldInput_s value;
  string str;
  bool isnull;
} fieldValue_s;

typedef struct
{
  bool isrow;
  int64_t tableid;
  int64_t rowid; // used both for row's rowid, and index value
  int64_t fieldid;
  fieldValue_s fieldVal;
  int64_t engineid; // used with rowid for index value if
  bool deleteindexentry; // true = add, false = remove, for delete unique entry,
  // add/delete nonunique, add/delete null
  bool isnotaddunique; //simple flag for index entries that don't get pre-staged
  bool isreplace;
  int64_t newrowid;
  int64_t newengineid;
} rowOrField_s;

typedef struct
{
  operatortypes_e op;
  vector <fieldValue_s> values;
  string regexString;
} searchParams_s;

typedef struct
{
  int64_t rowid;
  int64_t engineid;
} nonLockingIndexEntry_s;

typedef nonLockingIndexEntry_s indexEntry_s;

typedef struct
{
  int64_t status;

  bool isrow;

  int64_t rowid;
  int64_t tableid;
  string row;
  locktype_e locktype;

  int64_t forward_rowid;
  int64_t forward_engineid;

  // for index
  int64_t fieldid;
  int64_t engineid; // index also uses rowid
  fieldValue_s fieldVal;

  // for select
  vector<nonLockingIndexEntry_s> indexHits;
  searchParams_s searchParameters;
  vector<int64_t> rowids;
  vector<returnRow_s> returnRows;
} subtransactionCmd_s;

typedef struct
{
  string node;
  string service;
  int epollfd;
} listenerStruct_s;

typedef struct
{
  int64_t resultCode;
  msgpack::sbuffer *sbuf;
} procedureResponse_s;

typedef struct
{
  int64_t rowid;
  int64_t tableid;
  int64_t engineid;
} uuRecord_s;

typedef struct
{
  locktype_e locktype;
  bool isrow; // false, is index
  int64_t rowid;
  int64_t tableid;
  int64_t engineid;

  // index entries are field value -> rowid,subtransactionid}
  int64_t fieldid;
  fieldtype_e fieldType;
  fieldValue_s fieldVal;
} locked_s;

typedef struct
{
  locktype_e locktype;
  int64_t engineid;
  fieldValue_s fieldVal;
} lockFieldValue_s;

typedef struct
{
  pendingprimitive_e cmd;

  string originalRow;
  int64_t originalrowid;
  int64_t originalengineid;
  int64_t previoussubtransactionid;
  string newRow;
  int64_t newrowid;
  int64_t newengineid;
  locktype_e locktype;
  // uniqueIndices[fieldid] = lockFieldValue
  boost::unordered_map< int64_t, lockFieldValue_s > uniqueIndices;
} stagedRow_s;

typedef boost::unordered_map<int64_t, class Schema *> domainidToSchemaMap;

void debug(char *, int, char *);

void trimspace(string &);

// flags for row & unique index entry manipulation
#define DELETEFLAG 0
#define INSERTFLAG 1
#define LOCKEDFLAG 2
#define LOCKTYPEFLAG 3 // 0 is READLOCK 1 is WRITELOCK
#define REPLACEDELETEFLAG 4

enum deadlockchange_e
{
  ADDLOCKEDENTRY = 1,
  ADDLOCKPENDINGENTRY,
  REMOVELOCKEDENTRY,
  REMOVELOCKPENDINGENTRY,
  TRANSITIONPENDINGTOLOCKEDENTRY
};

class Topology;
extern class Topology nodeTopology;
extern pthread_mutex_t nodeTopologyMutex;

void msgpack2Vector(vector<string> *, char *, int64_t);

char setdeleteflag(char *);
bool getdeleteflag(char);
char cleardeleteflag(char *);
char setinsertflag(char *);
bool getinsertflag(char);
char clearinsertflag(char *);
bool getlockedflag(char);
char clearlockedflag(char *);
locktype_e getlocktype(char);
// return false if a problem
bool setwritelock(char *);
bool setreadlock(char *);
char setreplacedeleteflag(char *);
bool getreplacedeleteflag(char);
char clearreplacedeleteflag(char *);
// end of flags stuff

int64_t getPartitionid(fieldValue_s &, fieldtype_e, int64_t);
void like2Regex(string &);
bool compareFields(fieldtype_e, const fieldValue_s &, const fieldValue_s &);
void stagedRow2ReturnRow(const stagedRow_s &, returnRow_s &);

#endif // DEFS_HPP
