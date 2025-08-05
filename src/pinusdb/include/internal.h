/*
* Copyright (c) 2019 ChangSha JuSong Soft Inc. <service@pinusdb.cn>.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; version 3 of the License.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with this program; If not, see <http://www.gnu.org/licenses>
*/

#pragma once

#ifdef _WIN32
#include <WinSock2.h>
#include <Windows.h>
#include <MSWSock.h>
#endif

#include <stdint.h>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <mutex>

#include "pdb.h"
#include "pdb_error.h"

#define PDB_SYS_DEV_CNT   100000
#define IP_ADDR_STR_LEN   16      //IP��ַ�ַ������ȣ�Ŀǰֻ����IPv4


#define PDB_KB_BYTES(k)     ((k) * 1024)
#define PDB_MB_BYTES(m)     ((size_t)(m) * 1024 * 1024)
#define PDB_GB_BYTES(g)     ((size_t)(g) * 1024 * 1024 * 1024)

#define PDB_PART_TYPE_NORMAL_STR    "normal"
#define PDB_PART_TYPE_COMPRESS_STR  "compress"
#define PDB_PART_TYPE_NORMAL_VAL    1
#define PDB_PART_TYPE_COMPRESS_VAL  2

#define NORMAL_DATA_FILE_HEAD_STR   "PDB NORMAL 2"
#define COMPRESS_DATA_FILE_HEAD_STR "PDB COMPRESS 2"

#define PDB_MAJOR_VER_VAL        3
#define PDB_MINOR_VER_VAL        0
#define PDB_BUILD_VER_VAL        2


#define PDB_BOOL_FALSE           0
#define PDB_BOOL_TRUE            1

#define NORMAL_PAGE_SIZE       (64 * 1024)
#define SYNC_PAGE_CNT          64

#define MAKE_DATAPART_MASK(tabCode, partCode)  ((((uint64_t)tabCode & 0xFF) << 56) | (((uint64_t)partCode & 0xFFFFFF) << 32))
#define MAKE_DATATABLE_MASK(tabCode)           (((uint64_t)tabCode & 0xFF) << 56)


#define DEVID_FIELD_NAME            "devid"
#define TSTAMP_FIELD_NAME           "tstamp"

#define DOUBLE_PRECISION         ((double)0.0000000001)
#define DOUBLE_EQUAL_ZERO(val)   (((val) < ((double)0.0000000001)) && ((val) > ((double)-0.0000000001)))

#define NORMAL_IDX_FILE_EXTEND               ".idx"       // ͨ�������ļ���չ��
#define NORMAL_DATA_FILE_EXTEND              ".dat"       // ͨ�������ļ���չ��
#define COMPRESS_DATA_FILE_EXTEND            ".cdat"      //

#define SNAPSHOT_NAME                 ".snapshot"
#define SNAPSHOT_NAME_LEN             (sizeof(SNAPSHOT_NAME) - 1)

#define PDB_USER_ROLE_READONLY_STR    "readOnly"
#define PDB_USER_ROLE_WRITEONLY_STR   "writeOnly"
#define PDB_USER_ROLE_READWRITE_STR   "readWrite"
#define PDB_USER_ROLE_ADMIN_STR       "admin"

/////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
#ifndef PDB_CONSTEXPR
#define PDB_CONSTEXPR constexpr
#endif

#else

#ifndef PDB_CONSTEXPR
#define PDB_CONSTEXPR 
#endif

#endif


/////////////////////////////////////////////////////////////////////////


///////////////////////////////�����ļ���غ����////////////////////////


#define PDB_PWD_CRC32_LEN      4  //�����CRC�볤��
#define PDB_ROLE_LEN           4  //��ɫ�ĳ���

#define PDB_DEVID_INDEX         0        // ���������±�
#define PDB_TSTAMP_INDEX        1        // ʱ������±�


#define PDB_QUERY_DEFAULT_COUNT            1000
#define PDB_QUERY_MAX_COUNT                10000

#define PDB_TABLE_MAX_FIELD_COUNT          (860)         // һ������������

#define PDB_MAX_PACKET_BODY_LEN      (4 * 1024 * 1024)  //ÿ��������󳤶�

//ÿ����¼� 8K
#define PDB_MAX_REC_LEN              8192

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

typedef struct _PdbStr
{
  const char* pStr_;
  size_t len_;
}PdbStr;

typedef struct _PdbBlob
{
  const uint8_t* pBlob_;
  size_t len_;
}PdbBlob;

typedef uint8_t PdbByte;

typedef struct _FieldInfoFormat
{
  char fieldName_[PDB_FILED_NAME_LEN];   //�ֶ���
  char fieldType_[4];   //�ֶ�����,int32_t
  char padding_[12];
}FieldInfoFormat;

enum PDB_SQL_FUNC{
  _FUNC_AGG_MINID_ = 0,
  FUNC_AGG_COUNT,
  FUNC_AGG_FIRST,
  FUNC_AGG_LAST,
  FUNC_AGG_AVG,
  FUNC_AGG_MIN,
  FUNC_AGG_MAX,
  FUNC_AGG_SUM,
  FUNC_AGG_COUNT_IF,
  FUNC_AGG_FIRST_IF,
  FUNC_AGG_LAST_IF,
  FUNC_AGG_AVG_IF,
  FUNC_AGG_MIN_IF,
  FUNC_AGG_MAX_IF,
  FUNC_AGG_SUM_IF,
  _FUNC_AGG_MAXID_,
  FUNC_ADD,
  FUNC_SUB,
  FUNC_MUL,
  FUNC_DIV,
  FUNC_MOD,
  FUNC_DATETIMEADD,
  FUNC_DATETIMEDIFF,
  FUNC_DATETIMEFLOOR,
  FUNC_DATETIMECEIL,
  FUNC_IF,
  FUNC_ABS,
  FUNC_NOW
};


typedef struct _LogRecInfo
{
  uint64_t tabCrc;
  uint32_t metaCrc;
  uint16_t recType;
  uint16_t recLen;
  int64_t devId;
  const char* pRec;
}LogRecInfo;
