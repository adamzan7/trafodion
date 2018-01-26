//**********************************************************************
// @@@ START COPYRIGHT @@@
//
// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
//
// @@@ END COPYRIGHT @@@
// **********************************************************************

#include "QRLogger.h"
#include "Globals.h"
#include "jni.h"
#include "HdfsClient_JNI.h"

// ===========================================================================
// ===== Class HdfsScan
// ===========================================================================

JavaMethodInit* HdfsScan::JavaMethods_ = NULL;
jclass HdfsScan::javaClass_ = 0;
bool HdfsScan::javaMethodsInitialized_ = false;
pthread_mutex_t HdfsScan::javaMethodsInitMutex_ = PTHREAD_MUTEX_INITIALIZER;

static const char* const hdfsScanErrorEnumStr[] = 
{
};

 
//////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////
HDFS_Scan_RetCode HdfsScan::init()
{
  static char className[]="org/trafodion/sql/HdfsScan";
  HDFS_Scan_RetCode rc; 

  if (javaMethodsInitialized_)
    return (HDFS_Scan_RetCode)JavaObjectInterface::init(className, javaClass_, JavaMethods_, (Int32)JM_LAST, javaMethodsInitialized_); 
  else
  {
    pthread_mutex_lock(&javaMethodsInitMutex_);
    if (javaMethodsInitialized_)
    {
      pthread_mutex_unlock(&javaMethodsInitMutex_);
      return (HDFS_Scan_RetCode)JavaObjectInterface::init(className, javaClass_, JavaMethods_, (Int32)JM_LAST, javaMethodsInitialized_);
    }
    JavaMethods_ = new JavaMethodInit[JM_LAST];
    
    JavaMethods_[JM_CTOR      ].jm_name      = "<init>";
    JavaMethods_[JM_CTOR      ].jm_signature = "()V";
    JavaMethods_[JM_INIT_SCAN_RANGES].jm_name      = "<init>";
    JavaMethods_[JM_INIT_SCAN_RANGES].jm_signature = "(Ljava/lang/Object;Ljava/lang/Object;[Ljava/lang/String;[J[J)V";
    JavaMethods_[JM_TRAF_HDFS_READ].jm_name      = "trafHdfsRead";
    JavaMethods_[JM_TRAF_HDFS_READ].jm_signature = "()[I";
   
    rc = (HDFS_Scan_RetCode)JavaObjectInterface::init(className, javaClass_, JavaMethods_, (Int32)JM_LAST, javaMethodsInitialized_);
    javaMethodsInitialized_ = TRUE;
    pthread_mutex_unlock(&javaMethodsInitMutex_);
  }
  return rc;
}
        
char* HdfsScan::getErrorText(HDFS_Scan_RetCode errEnum)
{
  if (errEnum < (HDFS_Scan_RetCode)JOI_LAST)
    return JavaObjectInterface::getErrorText((JOI_RetCode)errEnum);
  else
    return (char*)hdfsScanErrorEnumStr[errEnum-HDFS_SCAN_FIRST-1];
}
//////////////////////////////////////////////////////////////////////////////
HDFS_Scan_RetCode HdfsScan::initScanRanges()
{
   return HDFS_SCAN_OK; 
}

HDFS_Scan_RetCode HdfsScan::trafHdfsRead()
{
   return HDFS_SCAN_OK; 
}

// ===========================================================================
// ===== Class HdfsClient
// ===========================================================================

JavaMethodInit* HdfsClient::JavaMethods_ = NULL;
jclass HdfsClient::javaClass_ = 0;
bool HdfsClient::javaMethodsInitialized_ = false;
pthread_mutex_t HdfsClient::javaMethodsInitMutex_ = PTHREAD_MUTEX_INITIALIZER;

static const char* const hdfsClientErrorEnumStr[] = 
{
  "JNI NewStringUTF() in hdfsCreate()."
 ,"Java exception in hdfsCreate()."
 ,"JNI NewStringUTF() in hdfsWrite()."
 ,"Java exception in hdfsWrite()."
 ,"Java exception in hdfsClose()."
 ,"JNI NewStringUTF() in hdfsMergeFiles()."
 ,"Java exception in hdfsMergeFiles()."
 ,"JNI NewStringUTF() in hdfsCleanUnloadPath()."
 ,"Java exception in hdfsCleanUnloadPath()."
 ,"JNI NewStringUTF() in hdfsExists()."
 ,"Java exception in hdfsExists()."
 ,"JNI NewStringUTF() in hdfsDeletePath()."
 ,"Java exception in hdfsDeletePath()."
};

//////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////
HdfsClient *HdfsClient::newInstance(NAHeap *heap, HDFS_Client_RetCode &retCode)
{
   retCode = HDFS_CLIENT_OK;
   HdfsClient *hdfsClient = new (heap) HdfsClient(heap);
   if (hdfsClient != NULL) {
       retCode = hdfsClient->init();
       if (retCode != HDFS_CLIENT_OK)
       {
          NADELETE(hdfsClient, HdfsClient, heap);
          hdfsClient = NULL;
       }
   }
   return hdfsClient;
}

HDFS_Client_RetCode HdfsClient::init()
{
  static char className[]="org/trafodion/sql/HDFSClient";
  HDFS_Client_RetCode rc;
  
  if (javaMethodsInitialized_)
    return (HDFS_Client_RetCode)JavaObjectInterface::init(className, javaClass_, JavaMethods_, (Int32)JM_LAST, javaMethodsInitialized_);
  else
  {
    pthread_mutex_lock(&javaMethodsInitMutex_);
    if (javaMethodsInitialized_)
    {
      pthread_mutex_unlock(&javaMethodsInitMutex_);
      return (HDFS_Client_RetCode)JavaObjectInterface::init(className, javaClass_, JavaMethods_, (Int32)JM_LAST, javaMethodsInitialized_);
    }
    JavaMethods_ = new JavaMethodInit[JM_LAST];
    
    JavaMethods_[JM_CTOR      ].jm_name      = "<init>";
    JavaMethods_[JM_CTOR      ].jm_signature = "()V";
    JavaMethods_[JM_HDFS_CREATE     ].jm_name      = "hdfsCreate";
    JavaMethods_[JM_HDFS_CREATE     ].jm_signature = "(Ljava/lang/String;Z)Z";
    JavaMethods_[JM_HDFS_WRITE      ].jm_name      = "hdfsWrite";
    JavaMethods_[JM_HDFS_WRITE      ].jm_signature = "([BJ)Z";
    JavaMethods_[JM_HDFS_CLOSE      ].jm_name      = "hdfsClose";
    JavaMethods_[JM_HDFS_CLOSE      ].jm_signature = "()Z";
    JavaMethods_[JM_HDFS_MERGE_FILES].jm_name      = "hdfsMergeFiles";
    JavaMethods_[JM_HDFS_MERGE_FILES].jm_signature = "(Ljava/lang/String;Ljava/lang/String;)Z";
    JavaMethods_[JM_HDFS_CLEAN_UNLOAD_PATH].jm_name      = "hdfsCleanUnloadPath";
    JavaMethods_[JM_HDFS_CLEAN_UNLOAD_PATH].jm_signature = "(Ljava/lang/String;)Z";
    JavaMethods_[JM_HDFS_EXISTS].jm_name      = "hdfsExists";
    JavaMethods_[JM_HDFS_EXISTS].jm_signature = "(Ljava/lang/String;)Z";
    JavaMethods_[JM_HDFS_DELETE_PATH].jm_name      = "hdfsDeletePath";
    JavaMethods_[JM_HDFS_DELETE_PATH].jm_signature = "(Ljava/lang/String;)Z";
    rc = (HDFS_Client_RetCode)JavaObjectInterface::init(className, javaClass_, JavaMethods_, (Int32)JM_LAST, javaMethodsInitialized_);
    javaMethodsInitialized_ = TRUE;
    pthread_mutex_unlock(&javaMethodsInitMutex_);
  }
  return rc;
}

//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////
char* HdfsClient::getErrorText(HDFS_Client_RetCode errEnum)
{
  if (errEnum < (HDFS_Client_RetCode)HDFS_CLIENT_FIRST)
    return JavaObjectInterface::getErrorText((JOI_RetCode)errEnum);
  else
    return (char*)hdfsClientErrorEnumStr[errEnum-HDFS_CLIENT_FIRST];
}

HDFS_Client_RetCode HdfsClient::hdfsCreate(const char* path, NABoolean compress)
{
  QRLogger::log(CAT_SQL_HDFS_SEQ_FILE_WRITER, LL_DEBUG, "HdfsClient::hdfsCreate(%s) called.", path);

  if (initJNIEnv() != JOI_OK)
     return HDFS_CLIENT_ERROR_HDFS_CREATE_PARAM;

  jstring js_path = jenv_->NewStringUTF(path);
  if (js_path == NULL) {
    GetCliGlobals()->setJniErrorStr(getErrorText(HDFS_CLIENT_ERROR_HDFS_CREATE_PARAM));
    jenv_->PopLocalFrame(NULL);
    return HDFS_CLIENT_ERROR_HDFS_CREATE_PARAM;
  }

  jboolean j_compress = compress;

  tsRecentJMFromJNI = JavaMethods_[JM_HDFS_CREATE].jm_full_name;
  jboolean jresult = jenv_->CallBooleanMethod(javaObj_, JavaMethods_[JM_HDFS_CREATE].methodID, js_path, j_compress);

  if (jenv_->ExceptionCheck())
  {
    getExceptionDetails();
    logError(CAT_SQL_HBASE, __FILE__, __LINE__);
    logError(CAT_SQL_HBASE, "HdfsClient::hdfsCreate()", getLastError());
    jenv_->PopLocalFrame(NULL);
    return HDFS_CLIENT_ERROR_HDFS_CREATE_EXCEPTION;
  }

  if (jresult == false)
  {
    logError(CAT_SQL_HBASE, "HdfsClient::hdfsCreate()", getLastError());
    jenv_->PopLocalFrame(NULL);
    return HDFS_CLIENT_ERROR_HDFS_CREATE_PARAM;
  }

  jenv_->PopLocalFrame(NULL);
  return HDFS_CLIENT_OK;
}

//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////
HDFS_Client_RetCode HdfsClient::hdfsWrite(const char* data, Int64 len)
{
  QRLogger::log(CAT_SQL_HDFS_SEQ_FILE_WRITER, LL_DEBUG, "HdfsClient::hdfsWrite(%ld) called.", len);

  if (initJNIEnv() != JOI_OK)
     return HDFS_CLIENT_ERROR_HDFS_WRITE_EXCEPTION;

  //Write the requisite bytes into the file
  jbyteArray jbArray = jenv_->NewByteArray( len);
  if (!jbArray) {
    GetCliGlobals()->setJniErrorStr(getErrorText(HDFS_CLIENT_ERROR_HDFS_WRITE_PARAM));
    jenv_->PopLocalFrame(NULL);
    return HDFS_CLIENT_ERROR_HDFS_WRITE_PARAM;
  }
  jenv_->SetByteArrayRegion(jbArray, 0, len, (const jbyte*)data);

  jlong j_len = len;
  tsRecentJMFromJNI = JavaMethods_[JM_HDFS_WRITE].jm_full_name;
  jboolean jresult = jenv_->CallBooleanMethod(javaObj_, JavaMethods_[JM_HDFS_WRITE].methodID,jbArray , j_len);

  if (jenv_->ExceptionCheck())
  {
    getExceptionDetails();
    logError(CAT_SQL_HBASE, __FILE__, __LINE__);
    logError(CAT_SQL_HBASE, "HdfsClient::hdfsWrite()", getLastError());
    jenv_->PopLocalFrame(NULL);
    return HDFS_CLIENT_ERROR_HDFS_WRITE_EXCEPTION;
  }

  if (jresult == false)
  {
    logError(CAT_SQL_HBASE, "HdfsClient::hdfsWrite()", getLastError());
    jenv_->PopLocalFrame(NULL);
    return HDFS_CLIENT_ERROR_HDFS_WRITE_EXCEPTION;
  }


  jenv_->PopLocalFrame(NULL);
  return HDFS_CLIENT_OK;
}

//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////
HDFS_Client_RetCode HdfsClient::hdfsClose()
{
  QRLogger::log(CAT_SQL_HDFS_SEQ_FILE_WRITER, LL_DEBUG, "HdfsClient::close() called.");

  if (initJNIEnv() != JOI_OK)
     return HDFS_CLIENT_ERROR_HDFS_CLOSE_EXCEPTION;

  // String close();
  tsRecentJMFromJNI = JavaMethods_[JM_HDFS_CLOSE].jm_full_name;
  jboolean jresult = jenv_->CallBooleanMethod(javaObj_, JavaMethods_[JM_HDFS_CLOSE].methodID);

  if (jenv_->ExceptionCheck())
  {
    getExceptionDetails();
    logError(CAT_SQL_HBASE, __FILE__, __LINE__);
    logError(CAT_SQL_HBASE, "HdfsClient::hdfsClose()", getLastError());
    jenv_->PopLocalFrame(NULL);
    return HDFS_CLIENT_ERROR_HDFS_CLOSE_EXCEPTION;
  }

  if (jresult == false)
  {
    logError(CAT_SQL_HBASE, "HdfsClient::hdfsClose()", getLastError());
    jenv_->PopLocalFrame(NULL);
    return HDFS_CLIENT_ERROR_HDFS_CLOSE_EXCEPTION;
  }

  jenv_->PopLocalFrame(NULL);
  return HDFS_CLIENT_OK;
}

HDFS_Client_RetCode HdfsClient::hdfsCleanUnloadPath( const NAString& uldPath)
{
  QRLogger::log(CAT_SQL_HBASE, LL_DEBUG, "HdfsClient::hdfsCleanUnloadPath(%s) called.",
                                                                             uldPath.data());
  if (initJNIEnv() != JOI_OK)
     return HDFS_CLIENT_ERROR_HDFS_CLEANUP_PARAM;

  jstring js_UldPath = jenv_->NewStringUTF(uldPath.data());
  if (js_UldPath == NULL) {
    GetCliGlobals()->setJniErrorStr(getErrorText(HDFS_CLIENT_ERROR_HDFS_CLEANUP_PARAM));
    jenv_->PopLocalFrame(NULL);
    return HDFS_CLIENT_ERROR_HDFS_CLEANUP_PARAM;
  }

  tsRecentJMFromJNI = JavaMethods_[JM_HDFS_CLEAN_UNLOAD_PATH].jm_full_name;
  jboolean jresult = jenv_->CallBooleanMethod(javaObj_, JavaMethods_[JM_HDFS_CLEAN_UNLOAD_PATH].methodID, js_UldPath);

  if (jenv_->ExceptionCheck())
  {
    getExceptionDetails();
    logError(CAT_SQL_HBASE, __FILE__, __LINE__);
    logError(CAT_SQL_HBASE, "HdfsClient::hdfsCleanUnloadPath()", getLastError());
    jenv_->PopLocalFrame(NULL);
    return HDFS_CLIENT_ERROR_HDFS_CLEANUP_EXCEPTION;
  }

  jenv_->PopLocalFrame(NULL);
  return HDFS_CLIENT_OK;
}

HDFS_Client_RetCode HdfsClient::hdfsMergeFiles( const NAString& srcPath,
                                                const NAString& dstPath)
{
  QRLogger::log(CAT_SQL_HBASE, LL_DEBUG, "HdfsClient::hdfsMergeFiles(%s, %s) called.",
                  srcPath.data(), dstPath.data());

  if (initJNIEnv() != JOI_OK)
     return HDFS_CLIENT_ERROR_HDFS_MERGE_FILES_EXCEPTION;

  jstring js_SrcPath = jenv_->NewStringUTF(srcPath.data());

  if (js_SrcPath == NULL) {
     GetCliGlobals()->setJniErrorStr(getErrorText(HDFS_CLIENT_ERROR_HDFS_MERGE_FILES_PARAM));
     jenv_->PopLocalFrame(NULL);
     return HDFS_CLIENT_ERROR_HDFS_MERGE_FILES_PARAM;
  }
  jstring js_DstPath= jenv_->NewStringUTF(dstPath.data());
  if (js_DstPath == NULL) {
     GetCliGlobals()->setJniErrorStr(getErrorText(HDFS_CLIENT_ERROR_HDFS_MERGE_FILES_PARAM));
     jenv_->PopLocalFrame(NULL);
     return HDFS_CLIENT_ERROR_HDFS_MERGE_FILES_PARAM;
  }


  tsRecentJMFromJNI = JavaMethods_[JM_HDFS_MERGE_FILES].jm_full_name;
  jboolean jresult = jenv_->CallBooleanMethod(javaObj_, JavaMethods_[JM_HDFS_MERGE_FILES].methodID, js_SrcPath, js_DstPath);

  if (jenv_->ExceptionCheck())
  {
    getExceptionDetails();
    logError(CAT_SQL_HBASE, __FILE__, __LINE__);
    logError(CAT_SQL_HBASE, "HdfsClient::hdfsMergeFiles()", getLastError());
    jenv_->PopLocalFrame(NULL);
    return HDFS_CLIENT_ERROR_HDFS_MERGE_FILES_EXCEPTION;
  }

  if (jresult == false)
  {
    logError(CAT_SQL_HBASE, "HdfsClient::hdfsMergeFiles()", getLastError());
    jenv_->PopLocalFrame(NULL);
    return HDFS_CLIENT_ERROR_HDFS_MERGE_FILES_EXCEPTION;
  } 

  jenv_->PopLocalFrame(NULL);
  return HDFS_CLIENT_OK;
}

HDFS_Client_RetCode HdfsClient::hdfsDeletePath( const NAString& delPath)
{
  QRLogger::log(CAT_SQL_HBASE, LL_DEBUG, "HdfsClient::hdfsDeletePath(%s called.",
                  delPath.data());
  if (initJNIEnv() != JOI_OK)
     return HDFS_CLIENT_ERROR_HDFS_DELETE_PATH_EXCEPTION;

  jstring js_delPath = jenv_->NewStringUTF(delPath.data());
  if (js_delPath == NULL) {
     GetCliGlobals()->setJniErrorStr(getErrorText(HDFS_CLIENT_ERROR_HDFS_DELETE_PATH_PARAM));
     jenv_->PopLocalFrame(NULL);
     return HDFS_CLIENT_ERROR_HDFS_DELETE_PATH_PARAM;
  }


  tsRecentJMFromJNI = JavaMethods_[JM_HDFS_DELETE_PATH].jm_full_name;
  jboolean jresult = jenv_->CallBooleanMethod(javaObj_, JavaMethods_[JM_HDFS_DELETE_PATH].methodID, js_delPath);

  if (jenv_->ExceptionCheck())
  {
    getExceptionDetails();
    logError(CAT_SQL_HBASE, __FILE__, __LINE__);
    logError(CAT_SQL_HBASE, "HdfsClient::hdfsDeletePath()", getLastError());
    jenv_->PopLocalFrame(NULL);
    return HDFS_CLIENT_ERROR_HDFS_DELETE_PATH_EXCEPTION;
  }

  if (jresult == false)
  {
    logError(CAT_SQL_HBASE, "HdfsClient::hdfsDeletePath()", getLastError());
    jenv_->PopLocalFrame(NULL);
    return HDFS_CLIENT_ERROR_HDFS_DELETE_PATH_EXCEPTION;
  }

  jenv_->PopLocalFrame(NULL);
  return HDFS_CLIENT_OK;
}

HDFS_Client_RetCode HdfsClient::hdfsExists( const NAString& uldPath, NABoolean & exist)
{
  QRLogger::log(CAT_SQL_HBASE, LL_DEBUG, "HdfsClient::hdfsExists(%s) called.",
                                                      uldPath.data());

  if (initJNIEnv() != JOI_OK)
     return HDFS_CLIENT_ERROR_HDFS_EXISTS_EXCEPTION;

  jstring js_UldPath = jenv_->NewStringUTF(uldPath.data());
  if (js_UldPath == NULL) {
     jenv_->PopLocalFrame(NULL);
     return HDFS_CLIENT_ERROR_HDFS_EXISTS_PARAM;
  }

  tsRecentJMFromJNI = JavaMethods_[JM_HDFS_EXISTS].jm_full_name;
  jboolean jresult = jenv_->CallBooleanMethod(javaObj_, JavaMethods_[JM_HDFS_EXISTS].methodID, js_UldPath);

  exist = jresult;

  if (jenv_->ExceptionCheck())
  {
    getExceptionDetails();
    logError(CAT_SQL_HBASE, __FILE__, __LINE__);
    logError(CAT_SQL_HBASE, "HdfsClient::hdfsExists()", getLastError());
    jenv_->PopLocalFrame(NULL);
    return HDFS_CLIENT_ERROR_HDFS_EXISTS_EXCEPTION;
  } 

  jenv_->PopLocalFrame(NULL);
  return HDFS_CLIENT_OK;
}
