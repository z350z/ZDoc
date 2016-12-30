﻿//--------------------------------------------------------------------
// Microsoft OLE DB Test
//
// Copyright 1995-2000 Microsoft Corporation.
//
// @doc
//
// @module KAGTEST.H | KAGTEST header file for test modules.
//
//
// @rev 01 | 03-21-95 | Microsoft | Created
// @rev 02 | 09-06-95 | Microsoft | Updated
//

#ifndef _KAGTEST_H_
#define _KAGTEST_H_

#include "oledb.h" 			// OLE DB Header Files
#include "oledberr.h"
#include "msdasql.h"

#include "privlib.h"		//include private library, which includes
//the "transact.h"

#include "sql.h"			// For ODBC functions
#include "sqlext.h"

//-----------------------------------------------------------------------------
// String constants
//-----------------------------------------------------------------------------
const WCHAR g_wszKageraName[] = L"MSDASQL";

#define MAX_GETINFO_BUF		250

enum STATE_ENUM
{
    STATE_NO_DSO,
    STATE_UNINITIALIZED_DSO,
    STATE_INITIALIZED_DSO,
    STATE_INTI_ALREADY_UNINIT
};

enum GETINFO_ENUM
{
    E_ACCESSIBLE_PROCEDURES,
    E_ACCESSIBLE_TABLES,
    E_ACTIVE_ENVIRONMENTS,
    E_AGGREGATE_FUNCTIONS,
    E_ALTER_DOMAIN,
    E_ALTER_TABLE,
    E_ASYNC_MODE,
    E_BATCH_ROW_COUNT,
    E_BATCH_SUPPORT,
    E_CATALOG_LOCATION,
    E_CATALOG_NAME,
    E_CATALOG_NAME_SEPARATOR,
    E_CATALOG_USAGE,
    E_COLLATION_SEQ,
    E_CONVERT_INTERVAL_DAY_TIME,
    E_CONVERT_INTERVAL_YEAR_MONTH,
    E_CONVERT_WCHAR,
    E_CONVERT_WLONGVARCHAR,
    E_CONVERT_WVARCHAR,
    E_CREATE_ASSERTION,
    E_CREATE_CHARACTER_SET,
    E_CREATE_COLLATION,
    E_CREATE_DOMAIN,
    E_CREATE_SCHEMA,
    E_CREATE_TABLE,
    E_CREATE_TRANSLATION,
    E_CREATE_VIEW,
    E_CTALOG_TERM,
    E_CURSOR_COMMIT_BEHAVIOR,
    E_CURSOR_SENSITIVITY,
    E_DATA_SOURCE_NAME,
    E_DATA_SOURCE_READ_ONLY,
    E_DATETIME_LITERALS,
    E_DBMS_NAME,
    E_DBMS_VER,
    E_DDL_INDEX,
    E_DEFAULT_TXN_ISOLATION,
    E_DESCRIBE_PARAMETER,
    E_DM_VER,
    E_DRIVER_HDESC,
    E_DROP_ASSERTION,
    E_DROP_CHARACTER_SET,
    E_DROP_COLLATION,
    E_DROP_DOMAIN,
    E_DROP_SCHEMA,
    E_DROP_TABLE,
    E_DROP_TRANSLATION,
    E_DROP_VIEW,
    E_DYNAMIC_CURSOR_ATTRIBUTES1,
    E_DYNAMIC_CURSOR_ATTRIBUTES2,
    E_SQL_CONFORMANCE,
    E_FETCH_DIRECTION,
    E_FORWARD_ONLY_CURSOR_ATTRIBUTES1,
    E_FORWARD_ONLY_CURSOR_ATTRIBUTES2,
    E_GETDATA_EXTENSIONS,
    E_IDENTIFIER_CASE,
    E_IDENTIFIER_QUOTE_CHAR,
    E_INDEX_KEYWORDS,
    E_INFO_SCHEMA_VIEWS,
    E_INSERT_STATEMENT,
    E_INTEGRITY,
    E_KEYSET_CURSOR_ATTRIBUTES1,
    E_KEYSET_CURSOR_ATTRIBUTES2,
    E_MAX_ASYNC_CONCURRENT_STATEMENTS,
    E_MAX_CATALOG_NAME_LEN,
    E_MAX_COLUMN_NAME_LEN,
    E_MAX_COLUMNS_IN_GROUP_BY,
    E_MAX_COLUMNS_IN_INDEX,
    E_MAX_COLUMNS_IN_ORDER_BY,
    E_MAX_COLUMNS_IN_SELECT,
    E_MAX_COLUMNS_IN_TABLE,
    E_MAX_CONCURRENT_ACTIVITIES,
    E_MAX_CURSOR_NAME_LEN,
    E_MAX_DRIVER_CONNECTIONS,
    E_MAX_IDENTIFIER_LEN,
    E_MAX_INDEX_SIZE,
    E_MAX_ROW_SIZE,
    E_MAX_SCHEMA_NAME_LEN,
    E_MAX_STATEMENT_LEN,
    E_MAX_TABLE_NAME_LEN,
    E_MAX_TABLES_IN_SELECT,
    E_MAX_USER_NAME_LEN,
    E_MAXIMUM_CATALOG_NAME_LENGTH,
    E_MAXIMUM_COLUMN_NAME_LENGTH,
    E_MAXIMUM_COLUMNS_IN_GROUP_BY,
    E_MAXIMUM_COLUMNS_IN_INDEX,
    E_MAXIMUM_COLUMNS_IN_ORDER_BY,
    E_MAXIMUM_COLUMNS_IN_SELECT,
    E_MAXIMUM_CONCURRENT_ACTIVITIES,
    E_MAXIMUM_CURSOR_NAME_LENGTH,
    E_MAXIMUM_DRIVER_CONNECTIONS,
    E_MAXIMUM_IDENTIFIER_LENGTH,
    E_MAXIMUM_INDEX_SIZE,
    E_MAXIMUM_ROW_SIZE,
    E_MAXIMUM_SCHEMA_NAME_LENGTH,
    E_MAXIMUM_STATEMENT_LENGTH,
    E_MAXIMUM_TABLES_IN_SELECT,
    E_MAXIMUM_USER_NAME_LENGTH,
    E_NULL_COLLATION,
    E_ODBC_INTERFACE_CONFORMANCE,
    E_OJ_CAPABILITIES,
    E_ORDER_BY_COLUMNS_IN_SELECT,
    E_OUTER_JOIN_CAPABILITIES,
    E_PARAM_ARRAY_ROW_COUNTS,
    E_PARAM_ARRAY_SELECTS,
    E_SCHEMA_TERM,
    E_SCHEMA_USAGE,
    E_SCROLL_CONCURRENCY,
    E_SEARCH_PATTERN_ESCAPE,
    E_SERVER_NAME,
    E_SPECIAL_CHARACTERS,
    E_SQL92_DATETIME_FUNCTIONS,
    E_SQL92_FOREIGN_KEY_DELETE_RULE,
    E_SQL92_FOREIGN_KEY_UPDATE_RULE,
    E_SQL92_GRANT,
    E_SQL92_NUMERIC_VALUE_FUNCTIONS,
    E_SQL92_PREDICATES,
    E_SQL92_RELATIONAL_JOIN_OPERATORS,
    E_SQL92_REVOKE,
    E_SQL92_ROW_VALUE_CONSTRUCTOR,
    E_SQL92_STRING_FUNCTIONS,
    E_SQL92_VALUE_EXPRESSIONS,
    E_STANDARD_CLI_CONFORMANCE,
    E_STATIC_CURSOR_ATTRIBUTES1,
    E_STATIC_CURSOR_ATTRIBUTES2,
    E_TRANSACTION_CAPABLE,
    E_TRANSACTION_ISOLATION_OPTION,
    E_TXN_CAPABLE,
    E_TXN_ISOLATION_OPTION,
    E_UNION_STATEMENT,
    E_USER_NAME,
    E_XOPEN_CLI_YEAR
};

struct InfoValues
{
    USHORT	InfoValue;			// The GetInfo value
    BOOL	fInit;				// Requires initialization
    BOOL	fDriverSpecific;	// Is driver specific
    VARTYPE vt;					// Variant type used for this GetInfo
    WCHAR	* pwszDBMSName;		// The name of the dbms if driver specific
} g_InfoValueList[] =
{
//											fDriver
//	GetInfo							fInit	Specific	vt			pwszDBMSName
    SQL_ACCESSIBLE_PROCEDURES,		TRUE,	FALSE,		VT_BSTR,	NULL,
    SQL_ACCESSIBLE_TABLES,			TRUE,	FALSE,		VT_BSTR,	NULL,
    SQL_ACTIVE_ENVIRONMENTS,		TRUE,	FALSE,		VT_UI2,		NULL,
    SQL_AGGREGATE_FUNCTIONS,		TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_ALTER_DOMAIN,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_ALTER_TABLE,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_ASYNC_MODE,					TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_BATCH_ROW_COUNT,			TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_BOOKMARK_PERSISTENCE,		TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CATALOG_LOCATION,			TRUE,	FALSE,		VT_UI2,		NULL,
    SQL_CATALOG_NAME,				TRUE,	FALSE,		VT_BSTR,	NULL,
    SQL_CATALOG_NAME_SEPARATOR,		TRUE,	FALSE,		VT_BSTR,	NULL,
    SQL_CATALOG_TERM,				TRUE,	FALSE,		VT_BSTR,	NULL,
    SQL_CATALOG_USAGE,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_COLLATION_SEQ,				TRUE,	FALSE,		VT_BSTR,	NULL,
    SQL_COLUMN_ALIAS,				TRUE,	FALSE,		VT_BSTR,	NULL,
    SQL_CONCAT_NULL_BEHAVIOR,		TRUE,	FALSE,		VT_UI2,		NULL,
    SQL_CONVERT_BIGINT,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CONVERT_BINARY,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CONVERT_BIT,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CONVERT_CHAR,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CONVERT_DATE,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CONVERT_DECIMAL,			TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CONVERT_DOUBLE,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CONVERT_FLOAT,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CONVERT_INTEGER,			TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CONVERT_INTERVAL_YEAR_MONTH,TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CONVERT_INTERVAL_DAY_TIME,	TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CONVERT_LONGVARBINARY,		TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CONVERT_LONGVARCHAR,		TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CONVERT_NUMERIC,			TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CONVERT_REAL,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CONVERT_SMALLINT,			TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CONVERT_TIME,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CONVERT_TIMESTAMP,			TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CONVERT_TINYINT,			TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CONVERT_VARBINARY,			TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CONVERT_VARCHAR,			TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CONVERT_FUNCTIONS,			TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CORRELATION_NAME,			TRUE,	FALSE,		VT_UI2,		NULL,
    SQL_CREATE_ASSERTION,			TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CREATE_CHARACTER_SET,		TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CREATE_COLLATION,			TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CREATE_DOMAIN,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CREATE_SCHEMA,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CREATE_TABLE,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CREATE_TRANSLATION,			TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CREATE_VIEW,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_CURSOR_COMMIT_BEHAVIOR,		TRUE,	FALSE,		VT_UI2,		NULL,
    SQL_CURSOR_ROLLBACK_BEHAVIOR,	TRUE,	FALSE,		VT_UI2,		NULL,
    SQL_CURSOR_SENSITIVITY,			TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_DATA_SOURCE_NAME,			TRUE,	FALSE,		VT_BSTR,	NULL,
    SQL_DATA_SOURCE_READ_ONLY,		TRUE,	FALSE,		VT_BSTR,	NULL,
    SQL_DATABASE_NAME,				TRUE,	FALSE,		VT_BSTR,	NULL,
    SQL_DATETIME_LITERALS,			TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_DBMS_NAME,					TRUE,	FALSE,		VT_BSTR,	NULL,
    SQL_DBMS_VER,					TRUE,	FALSE,		VT_BSTR,	NULL,
    SQL_DDL_INDEX,					TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_DEFAULT_TXN_ISOLATION,		TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_DESCRIBE_PARAMETER,			TRUE,	FALSE,		VT_BSTR,	NULL,
    SQL_DM_VER,						TRUE,	FALSE,		VT_BSTR,	NULL,
    SQL_DRIVER_HDBC,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_DRIVER_HENV,				FALSE,	FALSE,		VT_UI4,		NULL,
    SQL_DRIVER_HDESC,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_DRIVER_HLIB,				FALSE,	FALSE,		VT_UI4,		NULL,
    SQL_DRIVER_HSTMT,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_DRIVER_NAME,				TRUE,	FALSE,		VT_BSTR,	NULL,
    SQL_DRIVER_ODBC_VER,			TRUE,	FALSE,		VT_BSTR,	NULL,
    SQL_DRIVER_VER,					TRUE,	FALSE,		VT_BSTR,	NULL,
    SQL_DROP_ASSERTION,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_DROP_CHARACTER_SET,			TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_DROP_COLLATION,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_DROP_DOMAIN,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_DROP_SCHEMA,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_DROP_TABLE,					TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_DROP_VIEW,					TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_DYNAMIC_CURSOR_ATTRIBUTES1,	TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_DYNAMIC_CURSOR_ATTRIBUTES2,	TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_EXPRESSIONS_IN_ORDERBY,		TRUE,	FALSE,		VT_BSTR,	NULL,
    SQL_FILE_USAGE,					TRUE,	FALSE,		VT_UI2,		NULL,
    SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES1,TRUE,FALSE,		VT_UI4,		NULL,
    SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES2,TRUE,FALSE,		VT_UI4,		NULL,
    SQL_GETDATA_EXTENSIONS,			TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_GROUP_BY,					TRUE,	FALSE,		VT_UI2,		NULL,
    SQL_IDENTIFIER_CASE,			TRUE,	FALSE,		VT_UI2,		NULL,
    SQL_IDENTIFIER_QUOTE_CHAR,		TRUE,	FALSE,		VT_BSTR,	NULL,
    SQL_INDEX_KEYWORDS,				TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_INFO_SCHEMA_VIEWS,			TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_INSERT_STATEMENT,			TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_INTEGRITY,					TRUE,	FALSE,		VT_BSTR,	NULL,
    SQL_KEYSET_CURSOR_ATTRIBUTES1,	TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_KEYSET_CURSOR_ATTRIBUTES2,	TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_KEYWORDS,					TRUE,	FALSE,		VT_BSTR,	NULL,
    SQL_LIKE_ESCAPE_CLAUSE,			TRUE,	FALSE,		VT_BSTR,	NULL,
    SQL_MAX_ASYNC_CONCURRENT_STATEMENTS,TRUE,FALSE,		VT_UI4,		NULL,
    SQL_MAX_BINARY_LITERAL_LEN,		TRUE,	FALSE,		VT_UI2,		NULL,
    SQL_MAX_CATALOG_NAME_LEN,		TRUE,	FALSE,		VT_UI2,		NULL,
    SQL_MAX_CHAR_LITERAL_LEN,		TRUE,	FALSE,		VT_UI4,		NULL,
    SQL_MAX_COLUMN_NAME_LEN,		TRUE,	FALSE,		VT_UI2,		NULL,
    SQL_MAX_COLUMNS_IN_GROUP_BY,	TRUE,	FALSE,		VT_UI2,		NULL,
    SQL_MAX_COLUMNS_IN_INDEX,		TRUE,	FALSE,		VT_UI2,		NULL,
    SQL_MAX_COLUMNS_IN_ORDER_BY,	TRUE,	FALSE,		VT_UI2,		NULL,
    SQL_MAX_COLUMNS_IN_SELECT,		TRUE,	FALSE,		VT_UI2,		NULL,
    SQL_MAX_CONCURRENT_ACTIVITIES,	TRUE,	FALSE,		VT_UI2,		NULL,
    SQL_MAX_CURSOR_NAME_LEN,		TRUE,	FALSE,		VT_UI2,		NULL,
    SQL_MAX_DRIVER_CONNECTIONS,		TRUE,	FALSE,		VT_UI2,		NULL,
    SQL_MAX_IDENTIFIER_LEN,			TRUE,	FALSE,		VT_UI2,		NULL,
    SQL_MAX_INDEX_SIZE,				TRUE,	FALSE,		VT_UI4,		NULL
};



enum DIAGERRORFIELD_ENUM
{
    E_DIAG_CURSOR_ROW_COUNT,
    E_DIAG_DYNAMIC_FUNCTION,
    E_DIAG_DYNAMIC_FUNCTION_CODE,
    E_DIAG_NUMBER,
    E_DIAG_RETURNCODE,
    E_DIAG_DIAG_ROW_COUNT,
    E_DIAG_CLASS_ORGIN,
    E_DIAG_COLUMN_NUMBER,
    E_DIAG_CONNECTION_NAME,
    E_DIAG_MESSAGE_TEXT,
    E_DIAG_NATIVE,
    E_DIAG_ROW_NUMBER,
    E_DIAG_SERVER_NAME,
    E_DIAG_SQLSTATE,
    E_DIAG_SUBCLASS_ORIGIN
};

enum ERROR_NUMBER
{
    eERRORONE,
    eERRORTWO,
};

enum ERROR_HANDLE_ENUM
{
    eHENV,
    eHDBC,
    eHSTMT,
    eHDESC
};

KAGREQDIAG g_rgKagDiagAll[]=
{
//	field					field flag	field type
    KAGREQDIAGFLAGS_HEADER,	VT_I4,		SQL_DIAG_CURSOR_ROW_COUNT,
    KAGREQDIAGFLAGS_HEADER,	VT_BSTR,	SQL_DIAG_DYNAMIC_FUNCTION,
    KAGREQDIAGFLAGS_HEADER,	VT_I4,		SQL_DIAG_DYNAMIC_FUNCTION_CODE,
    KAGREQDIAGFLAGS_HEADER,	VT_I4,		SQL_DIAG_NUMBER,
    KAGREQDIAGFLAGS_HEADER,	VT_I2,		SQL_DIAG_RETURNCODE,
    KAGREQDIAGFLAGS_HEADER,	VT_I4,		SQL_DIAG_ROW_COUNT,
    KAGREQDIAGFLAGS_RECORD,	VT_BSTR,	SQL_DIAG_CLASS_ORIGIN,
    KAGREQDIAGFLAGS_RECORD,	VT_I4,		SQL_DIAG_COLUMN_NUMBER,
    KAGREQDIAGFLAGS_RECORD,	VT_BSTR,	SQL_DIAG_CONNECTION_NAME,
    KAGREQDIAGFLAGS_RECORD,	VT_BSTR,	SQL_DIAG_MESSAGE_TEXT,
    KAGREQDIAGFLAGS_RECORD,	VT_I4,		SQL_DIAG_NATIVE,
    KAGREQDIAGFLAGS_RECORD,	VT_I4,		SQL_DIAG_ROW_NUMBER,
    KAGREQDIAGFLAGS_RECORD,	VT_BSTR,	SQL_DIAG_SERVER_NAME,
    KAGREQDIAGFLAGS_RECORD,	VT_BSTR,	SQL_DIAG_SQLSTATE,
    KAGREQDIAGFLAGS_RECORD,	VT_BSTR,	SQL_DIAG_SUBCLASS_ORIGIN
};
const int g_ccAllDiagFields	= sizeof(g_rgKagDiagAll)/sizeof(KAGREQDIAG);


#endif 	//_KAGTEST_H_
