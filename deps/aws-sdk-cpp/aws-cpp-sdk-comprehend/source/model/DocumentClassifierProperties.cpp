﻿/*
* Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License").
* You may not use this file except in compliance with the License.
* A copy of the License is located at
*
*  http://aws.amazon.com/apache2.0
*
* or in the "license" file accompanying this file. This file is distributed
* on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
* express or implied. See the License for the specific language governing
* permissions and limitations under the License.
*/

#include <aws/comprehend/model/DocumentClassifierProperties.h>
#include <aws/core/utils/json/JsonSerializer.h>

#include <utility>

using namespace Aws::Utils::Json;
using namespace Aws::Utils;

namespace Aws
{
namespace Comprehend
{
namespace Model
{

DocumentClassifierProperties::DocumentClassifierProperties() : 
    m_documentClassifierArnHasBeenSet(false),
    m_languageCode(LanguageCode::NOT_SET),
    m_languageCodeHasBeenSet(false),
    m_status(ModelStatus::NOT_SET),
    m_statusHasBeenSet(false),
    m_messageHasBeenSet(false),
    m_submitTimeHasBeenSet(false),
    m_endTimeHasBeenSet(false),
    m_trainingStartTimeHasBeenSet(false),
    m_trainingEndTimeHasBeenSet(false),
    m_inputDataConfigHasBeenSet(false),
    m_classifierMetadataHasBeenSet(false),
    m_dataAccessRoleArnHasBeenSet(false),
    m_volumeKmsKeyIdHasBeenSet(false)
{
}

DocumentClassifierProperties::DocumentClassifierProperties(JsonView jsonValue) : 
    m_documentClassifierArnHasBeenSet(false),
    m_languageCode(LanguageCode::NOT_SET),
    m_languageCodeHasBeenSet(false),
    m_status(ModelStatus::NOT_SET),
    m_statusHasBeenSet(false),
    m_messageHasBeenSet(false),
    m_submitTimeHasBeenSet(false),
    m_endTimeHasBeenSet(false),
    m_trainingStartTimeHasBeenSet(false),
    m_trainingEndTimeHasBeenSet(false),
    m_inputDataConfigHasBeenSet(false),
    m_classifierMetadataHasBeenSet(false),
    m_dataAccessRoleArnHasBeenSet(false),
    m_volumeKmsKeyIdHasBeenSet(false)
{
  *this = jsonValue;
}

DocumentClassifierProperties& DocumentClassifierProperties::operator =(JsonView jsonValue)
{
  if(jsonValue.ValueExists("DocumentClassifierArn"))
  {
    m_documentClassifierArn = jsonValue.GetString("DocumentClassifierArn");

    m_documentClassifierArnHasBeenSet = true;
  }

  if(jsonValue.ValueExists("LanguageCode"))
  {
    m_languageCode = LanguageCodeMapper::GetLanguageCodeForName(jsonValue.GetString("LanguageCode"));

    m_languageCodeHasBeenSet = true;
  }

  if(jsonValue.ValueExists("Status"))
  {
    m_status = ModelStatusMapper::GetModelStatusForName(jsonValue.GetString("Status"));

    m_statusHasBeenSet = true;
  }

  if(jsonValue.ValueExists("Message"))
  {
    m_message = jsonValue.GetString("Message");

    m_messageHasBeenSet = true;
  }

  if(jsonValue.ValueExists("SubmitTime"))
  {
    m_submitTime = jsonValue.GetDouble("SubmitTime");

    m_submitTimeHasBeenSet = true;
  }

  if(jsonValue.ValueExists("EndTime"))
  {
    m_endTime = jsonValue.GetDouble("EndTime");

    m_endTimeHasBeenSet = true;
  }

  if(jsonValue.ValueExists("TrainingStartTime"))
  {
    m_trainingStartTime = jsonValue.GetDouble("TrainingStartTime");

    m_trainingStartTimeHasBeenSet = true;
  }

  if(jsonValue.ValueExists("TrainingEndTime"))
  {
    m_trainingEndTime = jsonValue.GetDouble("TrainingEndTime");

    m_trainingEndTimeHasBeenSet = true;
  }

  if(jsonValue.ValueExists("InputDataConfig"))
  {
    m_inputDataConfig = jsonValue.GetObject("InputDataConfig");

    m_inputDataConfigHasBeenSet = true;
  }

  if(jsonValue.ValueExists("ClassifierMetadata"))
  {
    m_classifierMetadata = jsonValue.GetObject("ClassifierMetadata");

    m_classifierMetadataHasBeenSet = true;
  }

  if(jsonValue.ValueExists("DataAccessRoleArn"))
  {
    m_dataAccessRoleArn = jsonValue.GetString("DataAccessRoleArn");

    m_dataAccessRoleArnHasBeenSet = true;
  }

  if(jsonValue.ValueExists("VolumeKmsKeyId"))
  {
    m_volumeKmsKeyId = jsonValue.GetString("VolumeKmsKeyId");

    m_volumeKmsKeyIdHasBeenSet = true;
  }

  return *this;
}

JsonValue DocumentClassifierProperties::Jsonize() const
{
  JsonValue payload;

  if(m_documentClassifierArnHasBeenSet)
  {
   payload.WithString("DocumentClassifierArn", m_documentClassifierArn);

  }

  if(m_languageCodeHasBeenSet)
  {
   payload.WithString("LanguageCode", LanguageCodeMapper::GetNameForLanguageCode(m_languageCode));
  }

  if(m_statusHasBeenSet)
  {
   payload.WithString("Status", ModelStatusMapper::GetNameForModelStatus(m_status));
  }

  if(m_messageHasBeenSet)
  {
   payload.WithString("Message", m_message);

  }

  if(m_submitTimeHasBeenSet)
  {
   payload.WithDouble("SubmitTime", m_submitTime.SecondsWithMSPrecision());
  }

  if(m_endTimeHasBeenSet)
  {
   payload.WithDouble("EndTime", m_endTime.SecondsWithMSPrecision());
  }

  if(m_trainingStartTimeHasBeenSet)
  {
   payload.WithDouble("TrainingStartTime", m_trainingStartTime.SecondsWithMSPrecision());
  }

  if(m_trainingEndTimeHasBeenSet)
  {
   payload.WithDouble("TrainingEndTime", m_trainingEndTime.SecondsWithMSPrecision());
  }

  if(m_inputDataConfigHasBeenSet)
  {
   payload.WithObject("InputDataConfig", m_inputDataConfig.Jsonize());

  }

  if(m_classifierMetadataHasBeenSet)
  {
   payload.WithObject("ClassifierMetadata", m_classifierMetadata.Jsonize());

  }

  if(m_dataAccessRoleArnHasBeenSet)
  {
   payload.WithString("DataAccessRoleArn", m_dataAccessRoleArn);

  }

  if(m_volumeKmsKeyIdHasBeenSet)
  {
   payload.WithString("VolumeKmsKeyId", m_volumeKmsKeyId);

  }

  return payload;
}

} // namespace Model
} // namespace Comprehend
} // namespace Aws