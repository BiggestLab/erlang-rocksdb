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

#pragma once
#include <aws/kms/KMS_EXPORTS.h>
#include <aws/kms/KMSErrors.h>
#include <aws/core/client/AWSError.h>
#include <aws/core/client/ClientConfiguration.h>
#include <aws/core/client/AWSClient.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/kms/model/CancelKeyDeletionResult.h>
#include <aws/kms/model/ConnectCustomKeyStoreResult.h>
#include <aws/kms/model/CreateCustomKeyStoreResult.h>
#include <aws/kms/model/CreateGrantResult.h>
#include <aws/kms/model/CreateKeyResult.h>
#include <aws/kms/model/DecryptResult.h>
#include <aws/kms/model/DeleteCustomKeyStoreResult.h>
#include <aws/kms/model/DescribeCustomKeyStoresResult.h>
#include <aws/kms/model/DescribeKeyResult.h>
#include <aws/kms/model/DisconnectCustomKeyStoreResult.h>
#include <aws/kms/model/EncryptResult.h>
#include <aws/kms/model/GenerateDataKeyResult.h>
#include <aws/kms/model/GenerateDataKeyWithoutPlaintextResult.h>
#include <aws/kms/model/GenerateRandomResult.h>
#include <aws/kms/model/GetKeyPolicyResult.h>
#include <aws/kms/model/GetKeyRotationStatusResult.h>
#include <aws/kms/model/GetParametersForImportResult.h>
#include <aws/kms/model/ImportKeyMaterialResult.h>
#include <aws/kms/model/ListAliasesResult.h>
#include <aws/kms/model/ListGrantsResult.h>
#include <aws/kms/model/ListKeyPoliciesResult.h>
#include <aws/kms/model/ListKeysResult.h>
#include <aws/kms/model/ListResourceTagsResult.h>
#include <aws/kms/model/ListRetirableGrantsResult.h>
#include <aws/kms/model/ReEncryptResult.h>
#include <aws/kms/model/ScheduleKeyDeletionResult.h>
#include <aws/kms/model/UpdateCustomKeyStoreResult.h>
#include <aws/core/NoResult.h>
#include <aws/core/client/AsyncCallerContext.h>
#include <aws/core/http/HttpTypes.h>
#include <future>
#include <functional>

namespace Aws
{

namespace Http
{
  class HttpClient;
  class HttpClientFactory;
} // namespace Http

namespace Utils
{
  template< typename R, typename E> class Outcome;

namespace Threading
{
  class Executor;
} // namespace Threading
} // namespace Utils

namespace Auth
{
  class AWSCredentials;
  class AWSCredentialsProvider;
} // namespace Auth

namespace Client
{
  class RetryStrategy;
} // namespace Client

namespace KMS
{

namespace Model
{
        class CancelKeyDeletionRequest;
        class ConnectCustomKeyStoreRequest;
        class CreateAliasRequest;
        class CreateCustomKeyStoreRequest;
        class CreateGrantRequest;
        class CreateKeyRequest;
        class DecryptRequest;
        class DeleteAliasRequest;
        class DeleteCustomKeyStoreRequest;
        class DeleteImportedKeyMaterialRequest;
        class DescribeCustomKeyStoresRequest;
        class DescribeKeyRequest;
        class DisableKeyRequest;
        class DisableKeyRotationRequest;
        class DisconnectCustomKeyStoreRequest;
        class EnableKeyRequest;
        class EnableKeyRotationRequest;
        class EncryptRequest;
        class GenerateDataKeyRequest;
        class GenerateDataKeyWithoutPlaintextRequest;
        class GenerateRandomRequest;
        class GetKeyPolicyRequest;
        class GetKeyRotationStatusRequest;
        class GetParametersForImportRequest;
        class ImportKeyMaterialRequest;
        class ListAliasesRequest;
        class ListGrantsRequest;
        class ListKeyPoliciesRequest;
        class ListKeysRequest;
        class ListResourceTagsRequest;
        class ListRetirableGrantsRequest;
        class PutKeyPolicyRequest;
        class ReEncryptRequest;
        class RetireGrantRequest;
        class RevokeGrantRequest;
        class ScheduleKeyDeletionRequest;
        class TagResourceRequest;
        class UntagResourceRequest;
        class UpdateAliasRequest;
        class UpdateCustomKeyStoreRequest;
        class UpdateKeyDescriptionRequest;

        typedef Aws::Utils::Outcome<CancelKeyDeletionResult, Aws::Client::AWSError<KMSErrors>> CancelKeyDeletionOutcome;
        typedef Aws::Utils::Outcome<ConnectCustomKeyStoreResult, Aws::Client::AWSError<KMSErrors>> ConnectCustomKeyStoreOutcome;
        typedef Aws::Utils::Outcome<Aws::NoResult, Aws::Client::AWSError<KMSErrors>> CreateAliasOutcome;
        typedef Aws::Utils::Outcome<CreateCustomKeyStoreResult, Aws::Client::AWSError<KMSErrors>> CreateCustomKeyStoreOutcome;
        typedef Aws::Utils::Outcome<CreateGrantResult, Aws::Client::AWSError<KMSErrors>> CreateGrantOutcome;
        typedef Aws::Utils::Outcome<CreateKeyResult, Aws::Client::AWSError<KMSErrors>> CreateKeyOutcome;
        typedef Aws::Utils::Outcome<DecryptResult, Aws::Client::AWSError<KMSErrors>> DecryptOutcome;
        typedef Aws::Utils::Outcome<Aws::NoResult, Aws::Client::AWSError<KMSErrors>> DeleteAliasOutcome;
        typedef Aws::Utils::Outcome<DeleteCustomKeyStoreResult, Aws::Client::AWSError<KMSErrors>> DeleteCustomKeyStoreOutcome;
        typedef Aws::Utils::Outcome<Aws::NoResult, Aws::Client::AWSError<KMSErrors>> DeleteImportedKeyMaterialOutcome;
        typedef Aws::Utils::Outcome<DescribeCustomKeyStoresResult, Aws::Client::AWSError<KMSErrors>> DescribeCustomKeyStoresOutcome;
        typedef Aws::Utils::Outcome<DescribeKeyResult, Aws::Client::AWSError<KMSErrors>> DescribeKeyOutcome;
        typedef Aws::Utils::Outcome<Aws::NoResult, Aws::Client::AWSError<KMSErrors>> DisableKeyOutcome;
        typedef Aws::Utils::Outcome<Aws::NoResult, Aws::Client::AWSError<KMSErrors>> DisableKeyRotationOutcome;
        typedef Aws::Utils::Outcome<DisconnectCustomKeyStoreResult, Aws::Client::AWSError<KMSErrors>> DisconnectCustomKeyStoreOutcome;
        typedef Aws::Utils::Outcome<Aws::NoResult, Aws::Client::AWSError<KMSErrors>> EnableKeyOutcome;
        typedef Aws::Utils::Outcome<Aws::NoResult, Aws::Client::AWSError<KMSErrors>> EnableKeyRotationOutcome;
        typedef Aws::Utils::Outcome<EncryptResult, Aws::Client::AWSError<KMSErrors>> EncryptOutcome;
        typedef Aws::Utils::Outcome<GenerateDataKeyResult, Aws::Client::AWSError<KMSErrors>> GenerateDataKeyOutcome;
        typedef Aws::Utils::Outcome<GenerateDataKeyWithoutPlaintextResult, Aws::Client::AWSError<KMSErrors>> GenerateDataKeyWithoutPlaintextOutcome;
        typedef Aws::Utils::Outcome<GenerateRandomResult, Aws::Client::AWSError<KMSErrors>> GenerateRandomOutcome;
        typedef Aws::Utils::Outcome<GetKeyPolicyResult, Aws::Client::AWSError<KMSErrors>> GetKeyPolicyOutcome;
        typedef Aws::Utils::Outcome<GetKeyRotationStatusResult, Aws::Client::AWSError<KMSErrors>> GetKeyRotationStatusOutcome;
        typedef Aws::Utils::Outcome<GetParametersForImportResult, Aws::Client::AWSError<KMSErrors>> GetParametersForImportOutcome;
        typedef Aws::Utils::Outcome<ImportKeyMaterialResult, Aws::Client::AWSError<KMSErrors>> ImportKeyMaterialOutcome;
        typedef Aws::Utils::Outcome<ListAliasesResult, Aws::Client::AWSError<KMSErrors>> ListAliasesOutcome;
        typedef Aws::Utils::Outcome<ListGrantsResult, Aws::Client::AWSError<KMSErrors>> ListGrantsOutcome;
        typedef Aws::Utils::Outcome<ListKeyPoliciesResult, Aws::Client::AWSError<KMSErrors>> ListKeyPoliciesOutcome;
        typedef Aws::Utils::Outcome<ListKeysResult, Aws::Client::AWSError<KMSErrors>> ListKeysOutcome;
        typedef Aws::Utils::Outcome<ListResourceTagsResult, Aws::Client::AWSError<KMSErrors>> ListResourceTagsOutcome;
        typedef Aws::Utils::Outcome<ListRetirableGrantsResult, Aws::Client::AWSError<KMSErrors>> ListRetirableGrantsOutcome;
        typedef Aws::Utils::Outcome<Aws::NoResult, Aws::Client::AWSError<KMSErrors>> PutKeyPolicyOutcome;
        typedef Aws::Utils::Outcome<ReEncryptResult, Aws::Client::AWSError<KMSErrors>> ReEncryptOutcome;
        typedef Aws::Utils::Outcome<Aws::NoResult, Aws::Client::AWSError<KMSErrors>> RetireGrantOutcome;
        typedef Aws::Utils::Outcome<Aws::NoResult, Aws::Client::AWSError<KMSErrors>> RevokeGrantOutcome;
        typedef Aws::Utils::Outcome<ScheduleKeyDeletionResult, Aws::Client::AWSError<KMSErrors>> ScheduleKeyDeletionOutcome;
        typedef Aws::Utils::Outcome<Aws::NoResult, Aws::Client::AWSError<KMSErrors>> TagResourceOutcome;
        typedef Aws::Utils::Outcome<Aws::NoResult, Aws::Client::AWSError<KMSErrors>> UntagResourceOutcome;
        typedef Aws::Utils::Outcome<Aws::NoResult, Aws::Client::AWSError<KMSErrors>> UpdateAliasOutcome;
        typedef Aws::Utils::Outcome<UpdateCustomKeyStoreResult, Aws::Client::AWSError<KMSErrors>> UpdateCustomKeyStoreOutcome;
        typedef Aws::Utils::Outcome<Aws::NoResult, Aws::Client::AWSError<KMSErrors>> UpdateKeyDescriptionOutcome;

        typedef std::future<CancelKeyDeletionOutcome> CancelKeyDeletionOutcomeCallable;
        typedef std::future<ConnectCustomKeyStoreOutcome> ConnectCustomKeyStoreOutcomeCallable;
        typedef std::future<CreateAliasOutcome> CreateAliasOutcomeCallable;
        typedef std::future<CreateCustomKeyStoreOutcome> CreateCustomKeyStoreOutcomeCallable;
        typedef std::future<CreateGrantOutcome> CreateGrantOutcomeCallable;
        typedef std::future<CreateKeyOutcome> CreateKeyOutcomeCallable;
        typedef std::future<DecryptOutcome> DecryptOutcomeCallable;
        typedef std::future<DeleteAliasOutcome> DeleteAliasOutcomeCallable;
        typedef std::future<DeleteCustomKeyStoreOutcome> DeleteCustomKeyStoreOutcomeCallable;
        typedef std::future<DeleteImportedKeyMaterialOutcome> DeleteImportedKeyMaterialOutcomeCallable;
        typedef std::future<DescribeCustomKeyStoresOutcome> DescribeCustomKeyStoresOutcomeCallable;
        typedef std::future<DescribeKeyOutcome> DescribeKeyOutcomeCallable;
        typedef std::future<DisableKeyOutcome> DisableKeyOutcomeCallable;
        typedef std::future<DisableKeyRotationOutcome> DisableKeyRotationOutcomeCallable;
        typedef std::future<DisconnectCustomKeyStoreOutcome> DisconnectCustomKeyStoreOutcomeCallable;
        typedef std::future<EnableKeyOutcome> EnableKeyOutcomeCallable;
        typedef std::future<EnableKeyRotationOutcome> EnableKeyRotationOutcomeCallable;
        typedef std::future<EncryptOutcome> EncryptOutcomeCallable;
        typedef std::future<GenerateDataKeyOutcome> GenerateDataKeyOutcomeCallable;
        typedef std::future<GenerateDataKeyWithoutPlaintextOutcome> GenerateDataKeyWithoutPlaintextOutcomeCallable;
        typedef std::future<GenerateRandomOutcome> GenerateRandomOutcomeCallable;
        typedef std::future<GetKeyPolicyOutcome> GetKeyPolicyOutcomeCallable;
        typedef std::future<GetKeyRotationStatusOutcome> GetKeyRotationStatusOutcomeCallable;
        typedef std::future<GetParametersForImportOutcome> GetParametersForImportOutcomeCallable;
        typedef std::future<ImportKeyMaterialOutcome> ImportKeyMaterialOutcomeCallable;
        typedef std::future<ListAliasesOutcome> ListAliasesOutcomeCallable;
        typedef std::future<ListGrantsOutcome> ListGrantsOutcomeCallable;
        typedef std::future<ListKeyPoliciesOutcome> ListKeyPoliciesOutcomeCallable;
        typedef std::future<ListKeysOutcome> ListKeysOutcomeCallable;
        typedef std::future<ListResourceTagsOutcome> ListResourceTagsOutcomeCallable;
        typedef std::future<ListRetirableGrantsOutcome> ListRetirableGrantsOutcomeCallable;
        typedef std::future<PutKeyPolicyOutcome> PutKeyPolicyOutcomeCallable;
        typedef std::future<ReEncryptOutcome> ReEncryptOutcomeCallable;
        typedef std::future<RetireGrantOutcome> RetireGrantOutcomeCallable;
        typedef std::future<RevokeGrantOutcome> RevokeGrantOutcomeCallable;
        typedef std::future<ScheduleKeyDeletionOutcome> ScheduleKeyDeletionOutcomeCallable;
        typedef std::future<TagResourceOutcome> TagResourceOutcomeCallable;
        typedef std::future<UntagResourceOutcome> UntagResourceOutcomeCallable;
        typedef std::future<UpdateAliasOutcome> UpdateAliasOutcomeCallable;
        typedef std::future<UpdateCustomKeyStoreOutcome> UpdateCustomKeyStoreOutcomeCallable;
        typedef std::future<UpdateKeyDescriptionOutcome> UpdateKeyDescriptionOutcomeCallable;
} // namespace Model

  class KMSClient;

    typedef std::function<void(const KMSClient*, const Model::CancelKeyDeletionRequest&, const Model::CancelKeyDeletionOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > CancelKeyDeletionResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::ConnectCustomKeyStoreRequest&, const Model::ConnectCustomKeyStoreOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > ConnectCustomKeyStoreResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::CreateAliasRequest&, const Model::CreateAliasOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > CreateAliasResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::CreateCustomKeyStoreRequest&, const Model::CreateCustomKeyStoreOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > CreateCustomKeyStoreResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::CreateGrantRequest&, const Model::CreateGrantOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > CreateGrantResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::CreateKeyRequest&, const Model::CreateKeyOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > CreateKeyResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::DecryptRequest&, const Model::DecryptOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > DecryptResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::DeleteAliasRequest&, const Model::DeleteAliasOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > DeleteAliasResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::DeleteCustomKeyStoreRequest&, const Model::DeleteCustomKeyStoreOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > DeleteCustomKeyStoreResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::DeleteImportedKeyMaterialRequest&, const Model::DeleteImportedKeyMaterialOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > DeleteImportedKeyMaterialResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::DescribeCustomKeyStoresRequest&, const Model::DescribeCustomKeyStoresOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > DescribeCustomKeyStoresResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::DescribeKeyRequest&, const Model::DescribeKeyOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > DescribeKeyResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::DisableKeyRequest&, const Model::DisableKeyOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > DisableKeyResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::DisableKeyRotationRequest&, const Model::DisableKeyRotationOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > DisableKeyRotationResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::DisconnectCustomKeyStoreRequest&, const Model::DisconnectCustomKeyStoreOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > DisconnectCustomKeyStoreResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::EnableKeyRequest&, const Model::EnableKeyOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > EnableKeyResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::EnableKeyRotationRequest&, const Model::EnableKeyRotationOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > EnableKeyRotationResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::EncryptRequest&, const Model::EncryptOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > EncryptResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::GenerateDataKeyRequest&, const Model::GenerateDataKeyOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > GenerateDataKeyResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::GenerateDataKeyWithoutPlaintextRequest&, const Model::GenerateDataKeyWithoutPlaintextOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > GenerateDataKeyWithoutPlaintextResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::GenerateRandomRequest&, const Model::GenerateRandomOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > GenerateRandomResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::GetKeyPolicyRequest&, const Model::GetKeyPolicyOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > GetKeyPolicyResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::GetKeyRotationStatusRequest&, const Model::GetKeyRotationStatusOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > GetKeyRotationStatusResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::GetParametersForImportRequest&, const Model::GetParametersForImportOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > GetParametersForImportResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::ImportKeyMaterialRequest&, const Model::ImportKeyMaterialOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > ImportKeyMaterialResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::ListAliasesRequest&, const Model::ListAliasesOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > ListAliasesResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::ListGrantsRequest&, const Model::ListGrantsOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > ListGrantsResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::ListKeyPoliciesRequest&, const Model::ListKeyPoliciesOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > ListKeyPoliciesResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::ListKeysRequest&, const Model::ListKeysOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > ListKeysResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::ListResourceTagsRequest&, const Model::ListResourceTagsOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > ListResourceTagsResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::ListRetirableGrantsRequest&, const Model::ListRetirableGrantsOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > ListRetirableGrantsResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::PutKeyPolicyRequest&, const Model::PutKeyPolicyOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > PutKeyPolicyResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::ReEncryptRequest&, const Model::ReEncryptOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > ReEncryptResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::RetireGrantRequest&, const Model::RetireGrantOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > RetireGrantResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::RevokeGrantRequest&, const Model::RevokeGrantOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > RevokeGrantResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::ScheduleKeyDeletionRequest&, const Model::ScheduleKeyDeletionOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > ScheduleKeyDeletionResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::TagResourceRequest&, const Model::TagResourceOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > TagResourceResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::UntagResourceRequest&, const Model::UntagResourceOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > UntagResourceResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::UpdateAliasRequest&, const Model::UpdateAliasOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > UpdateAliasResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::UpdateCustomKeyStoreRequest&, const Model::UpdateCustomKeyStoreOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > UpdateCustomKeyStoreResponseReceivedHandler;
    typedef std::function<void(const KMSClient*, const Model::UpdateKeyDescriptionRequest&, const Model::UpdateKeyDescriptionOutcome&, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) > UpdateKeyDescriptionResponseReceivedHandler;

  /**
   * <fullname>AWS Key Management Service</fullname> <p>AWS Key Management Service
   * (AWS KMS) is an encryption and key management web service. This guide describes
   * the AWS KMS operations that you can call programmatically. For general
   * information about AWS KMS, see the <a
   * href="http://docs.aws.amazon.com/kms/latest/developerguide/"> <i>AWS Key
   * Management Service Developer Guide</i> </a>.</p> <note> <p>AWS provides SDKs
   * that consist of libraries and sample code for various programming languages and
   * platforms (Java, Ruby, .Net, macOS, Android, etc.). The SDKs provide a
   * convenient way to create programmatic access to AWS KMS and other AWS services.
   * For example, the SDKs take care of tasks such as signing requests (see below),
   * managing errors, and retrying requests automatically. For more information about
   * the AWS SDKs, including how to download and install them, see <a
   * href="http://aws.amazon.com/tools/">Tools for Amazon Web Services</a>.</p>
   * </note> <p>We recommend that you use the AWS SDKs to make programmatic API calls
   * to AWS KMS.</p> <p>Clients must support TLS (Transport Layer Security) 1.0. We
   * recommend TLS 1.2. Clients must also support cipher suites with Perfect Forward
   * Secrecy (PFS) such as Ephemeral Diffie-Hellman (DHE) or Elliptic Curve Ephemeral
   * Diffie-Hellman (ECDHE). Most modern systems such as Java 7 and later support
   * these modes.</p> <p> <b>Signing Requests</b> </p> <p>Requests must be signed by
   * using an access key ID and a secret access key. We strongly recommend that you
   * <i>do not</i> use your AWS account (root) access key ID and secret key for
   * everyday work with AWS KMS. Instead, use the access key ID and secret access key
   * for an IAM user, or you can use the AWS Security Token Service to generate
   * temporary security credentials that you can use to sign requests.</p> <p>All AWS
   * KMS operations require <a
   * href="http://docs.aws.amazon.com/general/latest/gr/signature-version-4.html">Signature
   * Version 4</a>.</p> <p> <b>Logging API Requests</b> </p> <p>AWS KMS supports AWS
   * CloudTrail, a service that logs AWS API calls and related events for your AWS
   * account and delivers them to an Amazon S3 bucket that you specify. By using the
   * information collected by CloudTrail, you can determine what requests were made
   * to AWS KMS, who made the request, when it was made, and so on. To learn more
   * about CloudTrail, including how to turn it on and find your log files, see the
   * <a href="http://docs.aws.amazon.com/awscloudtrail/latest/userguide/">AWS
   * CloudTrail User Guide</a>.</p> <p> <b>Additional Resources</b> </p> <p>For more
   * information about credentials and request signing, see the following:</p> <ul>
   * <li> <p> <a
   * href="http://docs.aws.amazon.com/general/latest/gr/aws-security-credentials.html">AWS
   * Security Credentials</a> - This topic provides general information about the of
   * credentials used for accessing AWS.</p> </li> <li> <p> <a
   * href="http://docs.aws.amazon.com/IAM/latest/UserGuide/id_credentials_temp.html">Temporary
   * Security Credentials</a> - This section of the <i>IAM User Guide</i> describes
   * how to create and use temporary security credentials.</p> </li> <li> <p> <a
   * href="http://docs.aws.amazon.com/general/latest/gr/signature-version-4.html">Signature
   * Version 4 Signing Process</a> - This set of topics walks you through the process
   * of signing a request using an access key ID and a secret access key.</p> </li>
   * </ul> <p> <b>Commonly Used APIs</b> </p> <p>Of the APIs discussed in this guide,
   * the following will prove the most useful for most applications. You will likely
   * perform actions other than these, such as creating keys and assigning policies,
   * by using the console.</p> <ul> <li> <p> <a>Encrypt</a> </p> </li> <li> <p>
   * <a>Decrypt</a> </p> </li> <li> <p> <a>GenerateDataKey</a> </p> </li> <li> <p>
   * <a>GenerateDataKeyWithoutPlaintext</a> </p> </li> </ul>
   */
  class AWS_KMS_API KMSClient : public Aws::Client::AWSJsonClient
  {
    public:
      typedef Aws::Client::AWSJsonClient BASECLASS;

       /**
        * Initializes client to use DefaultCredentialProviderChain, with default http client factory, and optional client config. If client config
        * is not specified, it will be initialized to default values.
        */
        KMSClient(const Aws::Client::ClientConfiguration& clientConfiguration = Aws::Client::ClientConfiguration());

       /**
        * Initializes client to use SimpleAWSCredentialsProvider, with default http client factory, and optional client config. If client config
        * is not specified, it will be initialized to default values.
        */
        KMSClient(const Aws::Auth::AWSCredentials& credentials, const Aws::Client::ClientConfiguration& clientConfiguration = Aws::Client::ClientConfiguration());

       /**
        * Initializes client to use specified credentials provider with specified client config. If http client factory is not supplied,
        * the default http client factory will be used
        */
        KMSClient(const std::shared_ptr<Aws::Auth::AWSCredentialsProvider>& credentialsProvider,
            const Aws::Client::ClientConfiguration& clientConfiguration = Aws::Client::ClientConfiguration());

        virtual ~KMSClient();

        inline virtual const char* GetServiceClientName() const override { return "KMS"; }


        /**
         * <p>Cancels the deletion of a customer master key (CMK). When this operation is
         * successful, the CMK is set to the <code>Disabled</code> state. To enable a CMK,
         * use <a>EnableKey</a>. You cannot perform this operation on a CMK in a different
         * AWS account.</p> <p>For more information about scheduling and canceling deletion
         * of a CMK, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/deleting-keys.html">Deleting
         * Customer Master Keys</a> in the <i>AWS Key Management Service Developer
         * Guide</i>.</p> <p>The result of this operation varies with the key state of the
         * CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/CancelKeyDeletion">AWS
         * API Reference</a></p>
         */
        virtual Model::CancelKeyDeletionOutcome CancelKeyDeletion(const Model::CancelKeyDeletionRequest& request) const;

        /**
         * <p>Cancels the deletion of a customer master key (CMK). When this operation is
         * successful, the CMK is set to the <code>Disabled</code> state. To enable a CMK,
         * use <a>EnableKey</a>. You cannot perform this operation on a CMK in a different
         * AWS account.</p> <p>For more information about scheduling and canceling deletion
         * of a CMK, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/deleting-keys.html">Deleting
         * Customer Master Keys</a> in the <i>AWS Key Management Service Developer
         * Guide</i>.</p> <p>The result of this operation varies with the key state of the
         * CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/CancelKeyDeletion">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::CancelKeyDeletionOutcomeCallable CancelKeyDeletionCallable(const Model::CancelKeyDeletionRequest& request) const;

        /**
         * <p>Cancels the deletion of a customer master key (CMK). When this operation is
         * successful, the CMK is set to the <code>Disabled</code> state. To enable a CMK,
         * use <a>EnableKey</a>. You cannot perform this operation on a CMK in a different
         * AWS account.</p> <p>For more information about scheduling and canceling deletion
         * of a CMK, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/deleting-keys.html">Deleting
         * Customer Master Keys</a> in the <i>AWS Key Management Service Developer
         * Guide</i>.</p> <p>The result of this operation varies with the key state of the
         * CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/CancelKeyDeletion">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void CancelKeyDeletionAsync(const Model::CancelKeyDeletionRequest& request, const CancelKeyDeletionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Connects or reconnects a <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a> to its associated AWS CloudHSM cluster.</p> <p>The custom key
         * store must be connected before you can create customer master keys (CMKs) in the
         * key store or use the CMKs it contains. You can disconnect and reconnect a custom
         * key store at any time.</p> <p>To connect a custom key store, its associated AWS
         * CloudHSM cluster must have at least one active HSM. To get the number of active
         * HSMs in a cluster, use the <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/APIReference/API_DescribeClusters">DescribeClusters</a>
         * operation. To add HSMs to the cluster, use the <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/APIReference/API_CreateHsm">CreateHsm</a>
         * operation.</p> <p>The connection process can take an extended amount of time to
         * complete; up to 20 minutes. This operation starts the connection process, but it
         * does not wait for it to complete. When it succeeds, this operation quickly
         * returns an HTTP 200 response and a JSON object with no properties. However, this
         * response does not indicate that the custom key store is connected. To get the
         * connection state of the custom key store, use the <a>DescribeCustomKeyStores</a>
         * operation.</p> <p>During the connection process, AWS KMS finds the AWS CloudHSM
         * cluster that is associated with the custom key store, creates the connection
         * infrastructure, connects to the cluster, logs into the AWS CloudHSM client as
         * the <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-concepts.html#concept-kmsuser">
         * <code>kmsuser</code> crypto user</a> (CU), and rotates its password.</p> <p>The
         * <code>ConnectCustomKeyStore</code> operation might fail for various reasons. To
         * find the reason, use the <a>DescribeCustomKeyStores</a> operation and see the
         * <code>ConnectionErrorCode</code> in the response. For help interpreting the
         * <code>ConnectionErrorCode</code>, see <a>CustomKeyStoresListEntry</a>.</p> <p>To
         * fix the failure, use the <a>DisconnectCustomKeyStore</a> operation to disconnect
         * the custom key store, correct the error, use the <a>UpdateCustomKeyStore</a>
         * operation if necessary, and then use <code>ConnectCustomKeyStore</code>
         * again.</p> <p>If you are having trouble connecting or disconnecting a custom key
         * store, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/fix-keystore.html">Troubleshooting
         * a Custom Key Store</a> in the <i>AWS Key Management Service Developer
         * Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ConnectCustomKeyStore">AWS
         * API Reference</a></p>
         */
        virtual Model::ConnectCustomKeyStoreOutcome ConnectCustomKeyStore(const Model::ConnectCustomKeyStoreRequest& request) const;

        /**
         * <p>Connects or reconnects a <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a> to its associated AWS CloudHSM cluster.</p> <p>The custom key
         * store must be connected before you can create customer master keys (CMKs) in the
         * key store or use the CMKs it contains. You can disconnect and reconnect a custom
         * key store at any time.</p> <p>To connect a custom key store, its associated AWS
         * CloudHSM cluster must have at least one active HSM. To get the number of active
         * HSMs in a cluster, use the <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/APIReference/API_DescribeClusters">DescribeClusters</a>
         * operation. To add HSMs to the cluster, use the <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/APIReference/API_CreateHsm">CreateHsm</a>
         * operation.</p> <p>The connection process can take an extended amount of time to
         * complete; up to 20 minutes. This operation starts the connection process, but it
         * does not wait for it to complete. When it succeeds, this operation quickly
         * returns an HTTP 200 response and a JSON object with no properties. However, this
         * response does not indicate that the custom key store is connected. To get the
         * connection state of the custom key store, use the <a>DescribeCustomKeyStores</a>
         * operation.</p> <p>During the connection process, AWS KMS finds the AWS CloudHSM
         * cluster that is associated with the custom key store, creates the connection
         * infrastructure, connects to the cluster, logs into the AWS CloudHSM client as
         * the <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-concepts.html#concept-kmsuser">
         * <code>kmsuser</code> crypto user</a> (CU), and rotates its password.</p> <p>The
         * <code>ConnectCustomKeyStore</code> operation might fail for various reasons. To
         * find the reason, use the <a>DescribeCustomKeyStores</a> operation and see the
         * <code>ConnectionErrorCode</code> in the response. For help interpreting the
         * <code>ConnectionErrorCode</code>, see <a>CustomKeyStoresListEntry</a>.</p> <p>To
         * fix the failure, use the <a>DisconnectCustomKeyStore</a> operation to disconnect
         * the custom key store, correct the error, use the <a>UpdateCustomKeyStore</a>
         * operation if necessary, and then use <code>ConnectCustomKeyStore</code>
         * again.</p> <p>If you are having trouble connecting or disconnecting a custom key
         * store, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/fix-keystore.html">Troubleshooting
         * a Custom Key Store</a> in the <i>AWS Key Management Service Developer
         * Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ConnectCustomKeyStore">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::ConnectCustomKeyStoreOutcomeCallable ConnectCustomKeyStoreCallable(const Model::ConnectCustomKeyStoreRequest& request) const;

        /**
         * <p>Connects or reconnects a <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a> to its associated AWS CloudHSM cluster.</p> <p>The custom key
         * store must be connected before you can create customer master keys (CMKs) in the
         * key store or use the CMKs it contains. You can disconnect and reconnect a custom
         * key store at any time.</p> <p>To connect a custom key store, its associated AWS
         * CloudHSM cluster must have at least one active HSM. To get the number of active
         * HSMs in a cluster, use the <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/APIReference/API_DescribeClusters">DescribeClusters</a>
         * operation. To add HSMs to the cluster, use the <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/APIReference/API_CreateHsm">CreateHsm</a>
         * operation.</p> <p>The connection process can take an extended amount of time to
         * complete; up to 20 minutes. This operation starts the connection process, but it
         * does not wait for it to complete. When it succeeds, this operation quickly
         * returns an HTTP 200 response and a JSON object with no properties. However, this
         * response does not indicate that the custom key store is connected. To get the
         * connection state of the custom key store, use the <a>DescribeCustomKeyStores</a>
         * operation.</p> <p>During the connection process, AWS KMS finds the AWS CloudHSM
         * cluster that is associated with the custom key store, creates the connection
         * infrastructure, connects to the cluster, logs into the AWS CloudHSM client as
         * the <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-concepts.html#concept-kmsuser">
         * <code>kmsuser</code> crypto user</a> (CU), and rotates its password.</p> <p>The
         * <code>ConnectCustomKeyStore</code> operation might fail for various reasons. To
         * find the reason, use the <a>DescribeCustomKeyStores</a> operation and see the
         * <code>ConnectionErrorCode</code> in the response. For help interpreting the
         * <code>ConnectionErrorCode</code>, see <a>CustomKeyStoresListEntry</a>.</p> <p>To
         * fix the failure, use the <a>DisconnectCustomKeyStore</a> operation to disconnect
         * the custom key store, correct the error, use the <a>UpdateCustomKeyStore</a>
         * operation if necessary, and then use <code>ConnectCustomKeyStore</code>
         * again.</p> <p>If you are having trouble connecting or disconnecting a custom key
         * store, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/fix-keystore.html">Troubleshooting
         * a Custom Key Store</a> in the <i>AWS Key Management Service Developer
         * Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ConnectCustomKeyStore">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void ConnectCustomKeyStoreAsync(const Model::ConnectCustomKeyStoreRequest& request, const ConnectCustomKeyStoreResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Creates a display name for a customer master key (CMK). You can use an alias
         * to identify a CMK in selected operations, such as <a>Encrypt</a> and
         * <a>GenerateDataKey</a>. </p> <p>Each CMK can have multiple aliases, but each
         * alias points to only one CMK. The alias name must be unique in the AWS account
         * and region. To simplify code that runs in multiple regions, use the same alias
         * name, but point it to a different CMK in each region. </p> <p>Because an alias
         * is not a property of a CMK, you can delete and change the aliases of a CMK
         * without affecting the CMK. Also, aliases do not appear in the response from the
         * <a>DescribeKey</a> operation. To get the aliases of all CMKs, use the
         * <a>ListAliases</a> operation.</p> <p>An alias must start with the word
         * <code>alias</code> followed by a forward slash (<code>alias/</code>). The alias
         * name can contain only alphanumeric characters, forward slashes (/), underscores
         * (_), and dashes (-). Alias names cannot begin with <code>aws</code>; that alias
         * name prefix is reserved by Amazon Web Services (AWS).</p> <p>The alias and the
         * CMK it is mapped to must be in the same AWS account and the same region. You
         * cannot perform this operation on an alias in a different AWS account.</p> <p>To
         * map an existing alias to a different CMK, call <a>UpdateAlias</a>.</p> <p>The
         * result of this operation varies with the key state of the CMK. For details, see
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/CreateAlias">AWS API
         * Reference</a></p>
         */
        virtual Model::CreateAliasOutcome CreateAlias(const Model::CreateAliasRequest& request) const;

        /**
         * <p>Creates a display name for a customer master key (CMK). You can use an alias
         * to identify a CMK in selected operations, such as <a>Encrypt</a> and
         * <a>GenerateDataKey</a>. </p> <p>Each CMK can have multiple aliases, but each
         * alias points to only one CMK. The alias name must be unique in the AWS account
         * and region. To simplify code that runs in multiple regions, use the same alias
         * name, but point it to a different CMK in each region. </p> <p>Because an alias
         * is not a property of a CMK, you can delete and change the aliases of a CMK
         * without affecting the CMK. Also, aliases do not appear in the response from the
         * <a>DescribeKey</a> operation. To get the aliases of all CMKs, use the
         * <a>ListAliases</a> operation.</p> <p>An alias must start with the word
         * <code>alias</code> followed by a forward slash (<code>alias/</code>). The alias
         * name can contain only alphanumeric characters, forward slashes (/), underscores
         * (_), and dashes (-). Alias names cannot begin with <code>aws</code>; that alias
         * name prefix is reserved by Amazon Web Services (AWS).</p> <p>The alias and the
         * CMK it is mapped to must be in the same AWS account and the same region. You
         * cannot perform this operation on an alias in a different AWS account.</p> <p>To
         * map an existing alias to a different CMK, call <a>UpdateAlias</a>.</p> <p>The
         * result of this operation varies with the key state of the CMK. For details, see
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/CreateAlias">AWS API
         * Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::CreateAliasOutcomeCallable CreateAliasCallable(const Model::CreateAliasRequest& request) const;

        /**
         * <p>Creates a display name for a customer master key (CMK). You can use an alias
         * to identify a CMK in selected operations, such as <a>Encrypt</a> and
         * <a>GenerateDataKey</a>. </p> <p>Each CMK can have multiple aliases, but each
         * alias points to only one CMK. The alias name must be unique in the AWS account
         * and region. To simplify code that runs in multiple regions, use the same alias
         * name, but point it to a different CMK in each region. </p> <p>Because an alias
         * is not a property of a CMK, you can delete and change the aliases of a CMK
         * without affecting the CMK. Also, aliases do not appear in the response from the
         * <a>DescribeKey</a> operation. To get the aliases of all CMKs, use the
         * <a>ListAliases</a> operation.</p> <p>An alias must start with the word
         * <code>alias</code> followed by a forward slash (<code>alias/</code>). The alias
         * name can contain only alphanumeric characters, forward slashes (/), underscores
         * (_), and dashes (-). Alias names cannot begin with <code>aws</code>; that alias
         * name prefix is reserved by Amazon Web Services (AWS).</p> <p>The alias and the
         * CMK it is mapped to must be in the same AWS account and the same region. You
         * cannot perform this operation on an alias in a different AWS account.</p> <p>To
         * map an existing alias to a different CMK, call <a>UpdateAlias</a>.</p> <p>The
         * result of this operation varies with the key state of the CMK. For details, see
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/CreateAlias">AWS API
         * Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void CreateAliasAsync(const Model::CreateAliasRequest& request, const CreateAliasResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Creates a <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a> that is associated with an <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/userguide/clusters.html">AWS
         * CloudHSM cluster</a> that you own and manage.</p> <p>This operation is part of
         * the <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/custom-key-store-overview.html">Custom
         * Key Store feature</a> feature in AWS KMS, which combines the convenience and
         * extensive integration of AWS KMS with the isolation and control of a
         * single-tenant key store.</p> <p>When the operation completes successfully, it
         * returns the ID of the new custom key store. Before you can use your new custom
         * key store, you need to use the <a>ConnectCustomKeyStore</a> operation to connect
         * the new key store to its AWS CloudHSM cluster.</p> <p>The
         * <code>CreateCustomKeyStore</code> operation requires the following elements.</p>
         * <ul> <li> <p>You must specify an active AWS CloudHSM cluster in the same account
         * and AWS Region as the custom key store. You can use an existing cluster or <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/userguide/create-cluster.html">create
         * and activate a new AWS CloudHSM cluster</a> for the key store. AWS KMS does not
         * require exclusive use of the cluster.</p> </li> <li> <p>You must include the
         * content of the <i>trust anchor certificate</i> for the cluster. You created this
         * certificate, and saved it in the <code>customerCA.crt</code> file, when you <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/userguide/initialize-cluster.html#sign-csr">initialized
         * the cluster</a>.</p> </li> <li> <p>You must provide the password of the
         * dedicated <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-concepts.html#concept-kmsuser">
         * <code>kmsuser</code> crypto user</a> (CU) account in the cluster.</p> <p>Before
         * you create the custom key store, use the <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/userguide/cloudhsm_mgmt_util-createUser.html">createUser</a>
         * command in <code>cloudhsm_mgmt_util</code> to create <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-concepts.html#concept-kmsuser">a
         * crypto user (CU) named <code>kmsuser</code> </a>in specified AWS CloudHSM
         * cluster. AWS KMS uses the <code>kmsuser</code> CU account to create and manage
         * key material on your behalf. For instructions, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/create-keystore.html#before-keystore">Create
         * the kmsuser Crypto User</a> in the <i>AWS Key Management Service Developer
         * Guide</i>.</p> </li> </ul> <p>The AWS CloudHSM cluster that you specify must
         * meet the following requirements.</p> <ul> <li> <p>The cluster must be active and
         * be in the same AWS account and Region as the custom key store.</p> </li> <li>
         * <p>Each custom key store must be associated with a different AWS CloudHSM
         * cluster. The cluster cannot be associated with another custom key store or have
         * the same cluster certificate as a cluster that is associated with another custom
         * key store. To view the cluster certificate, use the AWS CloudHSM <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/APIReference/API_DescribeClusters.html">DescribeClusters</a>
         * operation. Clusters that share a backup history have the same cluster
         * certificate.</p> </li> <li> <p>The cluster must be configured with subnets in at
         * least two different Availability Zones in the Region. Because AWS CloudHSM is
         * not supported in all Availability Zones, we recommend that the cluster have
         * subnets in all Availability Zones in the Region.</p> </li> <li> <p>The cluster
         * must contain at least two active HSMs, each in a different Availability
         * Zone.</p> </li> </ul> <p>New custom key stores are not automatically connected.
         * After you create your custom key store, use the <a>ConnectCustomKeyStore</a>
         * operation to connect the custom key store to its associated AWS CloudHSM
         * cluster. Even if you are not going to use your custom key store immediately, you
         * might want to connect it to verify that all settings are correct and then
         * disconnect it until you are ready to use it.</p> <p>If this operation succeeds,
         * it returns the ID of the new custom key store. For help with failures, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/fix-keystore.html">Troubleshoot
         * a Custom Key Store</a> in the <i>AWS KMS Developer Guide</i>.</p><p><h3>See
         * Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/CreateCustomKeyStore">AWS
         * API Reference</a></p>
         */
        virtual Model::CreateCustomKeyStoreOutcome CreateCustomKeyStore(const Model::CreateCustomKeyStoreRequest& request) const;

        /**
         * <p>Creates a <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a> that is associated with an <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/userguide/clusters.html">AWS
         * CloudHSM cluster</a> that you own and manage.</p> <p>This operation is part of
         * the <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/custom-key-store-overview.html">Custom
         * Key Store feature</a> feature in AWS KMS, which combines the convenience and
         * extensive integration of AWS KMS with the isolation and control of a
         * single-tenant key store.</p> <p>When the operation completes successfully, it
         * returns the ID of the new custom key store. Before you can use your new custom
         * key store, you need to use the <a>ConnectCustomKeyStore</a> operation to connect
         * the new key store to its AWS CloudHSM cluster.</p> <p>The
         * <code>CreateCustomKeyStore</code> operation requires the following elements.</p>
         * <ul> <li> <p>You must specify an active AWS CloudHSM cluster in the same account
         * and AWS Region as the custom key store. You can use an existing cluster or <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/userguide/create-cluster.html">create
         * and activate a new AWS CloudHSM cluster</a> for the key store. AWS KMS does not
         * require exclusive use of the cluster.</p> </li> <li> <p>You must include the
         * content of the <i>trust anchor certificate</i> for the cluster. You created this
         * certificate, and saved it in the <code>customerCA.crt</code> file, when you <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/userguide/initialize-cluster.html#sign-csr">initialized
         * the cluster</a>.</p> </li> <li> <p>You must provide the password of the
         * dedicated <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-concepts.html#concept-kmsuser">
         * <code>kmsuser</code> crypto user</a> (CU) account in the cluster.</p> <p>Before
         * you create the custom key store, use the <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/userguide/cloudhsm_mgmt_util-createUser.html">createUser</a>
         * command in <code>cloudhsm_mgmt_util</code> to create <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-concepts.html#concept-kmsuser">a
         * crypto user (CU) named <code>kmsuser</code> </a>in specified AWS CloudHSM
         * cluster. AWS KMS uses the <code>kmsuser</code> CU account to create and manage
         * key material on your behalf. For instructions, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/create-keystore.html#before-keystore">Create
         * the kmsuser Crypto User</a> in the <i>AWS Key Management Service Developer
         * Guide</i>.</p> </li> </ul> <p>The AWS CloudHSM cluster that you specify must
         * meet the following requirements.</p> <ul> <li> <p>The cluster must be active and
         * be in the same AWS account and Region as the custom key store.</p> </li> <li>
         * <p>Each custom key store must be associated with a different AWS CloudHSM
         * cluster. The cluster cannot be associated with another custom key store or have
         * the same cluster certificate as a cluster that is associated with another custom
         * key store. To view the cluster certificate, use the AWS CloudHSM <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/APIReference/API_DescribeClusters.html">DescribeClusters</a>
         * operation. Clusters that share a backup history have the same cluster
         * certificate.</p> </li> <li> <p>The cluster must be configured with subnets in at
         * least two different Availability Zones in the Region. Because AWS CloudHSM is
         * not supported in all Availability Zones, we recommend that the cluster have
         * subnets in all Availability Zones in the Region.</p> </li> <li> <p>The cluster
         * must contain at least two active HSMs, each in a different Availability
         * Zone.</p> </li> </ul> <p>New custom key stores are not automatically connected.
         * After you create your custom key store, use the <a>ConnectCustomKeyStore</a>
         * operation to connect the custom key store to its associated AWS CloudHSM
         * cluster. Even if you are not going to use your custom key store immediately, you
         * might want to connect it to verify that all settings are correct and then
         * disconnect it until you are ready to use it.</p> <p>If this operation succeeds,
         * it returns the ID of the new custom key store. For help with failures, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/fix-keystore.html">Troubleshoot
         * a Custom Key Store</a> in the <i>AWS KMS Developer Guide</i>.</p><p><h3>See
         * Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/CreateCustomKeyStore">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::CreateCustomKeyStoreOutcomeCallable CreateCustomKeyStoreCallable(const Model::CreateCustomKeyStoreRequest& request) const;

        /**
         * <p>Creates a <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a> that is associated with an <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/userguide/clusters.html">AWS
         * CloudHSM cluster</a> that you own and manage.</p> <p>This operation is part of
         * the <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/custom-key-store-overview.html">Custom
         * Key Store feature</a> feature in AWS KMS, which combines the convenience and
         * extensive integration of AWS KMS with the isolation and control of a
         * single-tenant key store.</p> <p>When the operation completes successfully, it
         * returns the ID of the new custom key store. Before you can use your new custom
         * key store, you need to use the <a>ConnectCustomKeyStore</a> operation to connect
         * the new key store to its AWS CloudHSM cluster.</p> <p>The
         * <code>CreateCustomKeyStore</code> operation requires the following elements.</p>
         * <ul> <li> <p>You must specify an active AWS CloudHSM cluster in the same account
         * and AWS Region as the custom key store. You can use an existing cluster or <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/userguide/create-cluster.html">create
         * and activate a new AWS CloudHSM cluster</a> for the key store. AWS KMS does not
         * require exclusive use of the cluster.</p> </li> <li> <p>You must include the
         * content of the <i>trust anchor certificate</i> for the cluster. You created this
         * certificate, and saved it in the <code>customerCA.crt</code> file, when you <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/userguide/initialize-cluster.html#sign-csr">initialized
         * the cluster</a>.</p> </li> <li> <p>You must provide the password of the
         * dedicated <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-concepts.html#concept-kmsuser">
         * <code>kmsuser</code> crypto user</a> (CU) account in the cluster.</p> <p>Before
         * you create the custom key store, use the <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/userguide/cloudhsm_mgmt_util-createUser.html">createUser</a>
         * command in <code>cloudhsm_mgmt_util</code> to create <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-concepts.html#concept-kmsuser">a
         * crypto user (CU) named <code>kmsuser</code> </a>in specified AWS CloudHSM
         * cluster. AWS KMS uses the <code>kmsuser</code> CU account to create and manage
         * key material on your behalf. For instructions, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/create-keystore.html#before-keystore">Create
         * the kmsuser Crypto User</a> in the <i>AWS Key Management Service Developer
         * Guide</i>.</p> </li> </ul> <p>The AWS CloudHSM cluster that you specify must
         * meet the following requirements.</p> <ul> <li> <p>The cluster must be active and
         * be in the same AWS account and Region as the custom key store.</p> </li> <li>
         * <p>Each custom key store must be associated with a different AWS CloudHSM
         * cluster. The cluster cannot be associated with another custom key store or have
         * the same cluster certificate as a cluster that is associated with another custom
         * key store. To view the cluster certificate, use the AWS CloudHSM <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/APIReference/API_DescribeClusters.html">DescribeClusters</a>
         * operation. Clusters that share a backup history have the same cluster
         * certificate.</p> </li> <li> <p>The cluster must be configured with subnets in at
         * least two different Availability Zones in the Region. Because AWS CloudHSM is
         * not supported in all Availability Zones, we recommend that the cluster have
         * subnets in all Availability Zones in the Region.</p> </li> <li> <p>The cluster
         * must contain at least two active HSMs, each in a different Availability
         * Zone.</p> </li> </ul> <p>New custom key stores are not automatically connected.
         * After you create your custom key store, use the <a>ConnectCustomKeyStore</a>
         * operation to connect the custom key store to its associated AWS CloudHSM
         * cluster. Even if you are not going to use your custom key store immediately, you
         * might want to connect it to verify that all settings are correct and then
         * disconnect it until you are ready to use it.</p> <p>If this operation succeeds,
         * it returns the ID of the new custom key store. For help with failures, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/fix-keystore.html">Troubleshoot
         * a Custom Key Store</a> in the <i>AWS KMS Developer Guide</i>.</p><p><h3>See
         * Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/CreateCustomKeyStore">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void CreateCustomKeyStoreAsync(const Model::CreateCustomKeyStoreRequest& request, const CreateCustomKeyStoreResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Adds a grant to a customer master key (CMK). The grant specifies who can use
         * the CMK and under what conditions. When setting permissions, grants are an
         * alternative to key policies. </p> <p>To perform this operation on a CMK in a
         * different AWS account, specify the key ARN in the value of the
         * <code>KeyId</code> parameter. For more information about grants, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/grants.html">Grants</a>
         * in the <i>AWS Key Management Service Developer Guide</i>.</p> <p>The result of
         * this operation varies with the key state of the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/CreateGrant">AWS API
         * Reference</a></p>
         */
        virtual Model::CreateGrantOutcome CreateGrant(const Model::CreateGrantRequest& request) const;

        /**
         * <p>Adds a grant to a customer master key (CMK). The grant specifies who can use
         * the CMK and under what conditions. When setting permissions, grants are an
         * alternative to key policies. </p> <p>To perform this operation on a CMK in a
         * different AWS account, specify the key ARN in the value of the
         * <code>KeyId</code> parameter. For more information about grants, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/grants.html">Grants</a>
         * in the <i>AWS Key Management Service Developer Guide</i>.</p> <p>The result of
         * this operation varies with the key state of the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/CreateGrant">AWS API
         * Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::CreateGrantOutcomeCallable CreateGrantCallable(const Model::CreateGrantRequest& request) const;

        /**
         * <p>Adds a grant to a customer master key (CMK). The grant specifies who can use
         * the CMK and under what conditions. When setting permissions, grants are an
         * alternative to key policies. </p> <p>To perform this operation on a CMK in a
         * different AWS account, specify the key ARN in the value of the
         * <code>KeyId</code> parameter. For more information about grants, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/grants.html">Grants</a>
         * in the <i>AWS Key Management Service Developer Guide</i>.</p> <p>The result of
         * this operation varies with the key state of the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/CreateGrant">AWS API
         * Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void CreateGrantAsync(const Model::CreateGrantRequest& request, const CreateGrantResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Creates a customer master key (CMK) in the caller's AWS account.</p> <p>You
         * can use a CMK to encrypt small amounts of data (4 KiB or less) directly, but
         * CMKs are more commonly used to encrypt data keys, which are used to encrypt raw
         * data. For more information about data keys and the difference between CMKs and
         * data keys, see the following:</p> <ul> <li> <p>The <a>GenerateDataKey</a>
         * operation</p> </li> <li> <p> <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/concepts.html">AWS
         * Key Management Service Concepts</a> in the <i>AWS Key Management Service
         * Developer Guide</i> </p> </li> </ul> <p>If you plan to <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/importing-keys.html">import
         * key material</a>, use the <code>Origin</code> parameter with a value of
         * <code>EXTERNAL</code> to create a CMK with no key material.</p> <p>To create a
         * CMK in a <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a>, use <code>CustomKeyStoreId</code> parameter to specify the custom
         * key store. You must also use the <code>Origin</code> parameter with a value of
         * <code>AWS_CLOUDHSM</code>. The AWS CloudHSM cluster that is associated with the
         * custom key store must have at least two active HSMs, each in a different
         * Availability Zone in the Region.</p> <p>You cannot use this operation to create
         * a CMK in a different AWS account.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/CreateKey">AWS API
         * Reference</a></p>
         */
        virtual Model::CreateKeyOutcome CreateKey(const Model::CreateKeyRequest& request) const;

        /**
         * <p>Creates a customer master key (CMK) in the caller's AWS account.</p> <p>You
         * can use a CMK to encrypt small amounts of data (4 KiB or less) directly, but
         * CMKs are more commonly used to encrypt data keys, which are used to encrypt raw
         * data. For more information about data keys and the difference between CMKs and
         * data keys, see the following:</p> <ul> <li> <p>The <a>GenerateDataKey</a>
         * operation</p> </li> <li> <p> <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/concepts.html">AWS
         * Key Management Service Concepts</a> in the <i>AWS Key Management Service
         * Developer Guide</i> </p> </li> </ul> <p>If you plan to <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/importing-keys.html">import
         * key material</a>, use the <code>Origin</code> parameter with a value of
         * <code>EXTERNAL</code> to create a CMK with no key material.</p> <p>To create a
         * CMK in a <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a>, use <code>CustomKeyStoreId</code> parameter to specify the custom
         * key store. You must also use the <code>Origin</code> parameter with a value of
         * <code>AWS_CLOUDHSM</code>. The AWS CloudHSM cluster that is associated with the
         * custom key store must have at least two active HSMs, each in a different
         * Availability Zone in the Region.</p> <p>You cannot use this operation to create
         * a CMK in a different AWS account.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/CreateKey">AWS API
         * Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::CreateKeyOutcomeCallable CreateKeyCallable(const Model::CreateKeyRequest& request) const;

        /**
         * <p>Creates a customer master key (CMK) in the caller's AWS account.</p> <p>You
         * can use a CMK to encrypt small amounts of data (4 KiB or less) directly, but
         * CMKs are more commonly used to encrypt data keys, which are used to encrypt raw
         * data. For more information about data keys and the difference between CMKs and
         * data keys, see the following:</p> <ul> <li> <p>The <a>GenerateDataKey</a>
         * operation</p> </li> <li> <p> <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/concepts.html">AWS
         * Key Management Service Concepts</a> in the <i>AWS Key Management Service
         * Developer Guide</i> </p> </li> </ul> <p>If you plan to <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/importing-keys.html">import
         * key material</a>, use the <code>Origin</code> parameter with a value of
         * <code>EXTERNAL</code> to create a CMK with no key material.</p> <p>To create a
         * CMK in a <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a>, use <code>CustomKeyStoreId</code> parameter to specify the custom
         * key store. You must also use the <code>Origin</code> parameter with a value of
         * <code>AWS_CLOUDHSM</code>. The AWS CloudHSM cluster that is associated with the
         * custom key store must have at least two active HSMs, each in a different
         * Availability Zone in the Region.</p> <p>You cannot use this operation to create
         * a CMK in a different AWS account.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/CreateKey">AWS API
         * Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void CreateKeyAsync(const Model::CreateKeyRequest& request, const CreateKeyResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Decrypts ciphertext. Ciphertext is plaintext that has been previously
         * encrypted by using any of the following operations:</p> <ul> <li> <p>
         * <a>GenerateDataKey</a> </p> </li> <li> <p>
         * <a>GenerateDataKeyWithoutPlaintext</a> </p> </li> <li> <p> <a>Encrypt</a> </p>
         * </li> </ul> <p>Note that if a caller has been granted access permissions to all
         * keys (through, for example, IAM user policies that grant <code>Decrypt</code>
         * permission on all resources), then ciphertext encrypted by using keys in other
         * accounts where the key grants access to the caller can be decrypted. To remedy
         * this, we recommend that you do not grant <code>Decrypt</code> access in an IAM
         * user policy. Instead grant <code>Decrypt</code> access only in key policies. If
         * you must grant <code>Decrypt</code> access in an IAM user policy, you should
         * scope the resource to specific keys or to specific trusted accounts.</p> <p>The
         * result of this operation varies with the key state of the CMK. For details, see
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/Decrypt">AWS API
         * Reference</a></p>
         */
        virtual Model::DecryptOutcome Decrypt(const Model::DecryptRequest& request) const;

        /**
         * <p>Decrypts ciphertext. Ciphertext is plaintext that has been previously
         * encrypted by using any of the following operations:</p> <ul> <li> <p>
         * <a>GenerateDataKey</a> </p> </li> <li> <p>
         * <a>GenerateDataKeyWithoutPlaintext</a> </p> </li> <li> <p> <a>Encrypt</a> </p>
         * </li> </ul> <p>Note that if a caller has been granted access permissions to all
         * keys (through, for example, IAM user policies that grant <code>Decrypt</code>
         * permission on all resources), then ciphertext encrypted by using keys in other
         * accounts where the key grants access to the caller can be decrypted. To remedy
         * this, we recommend that you do not grant <code>Decrypt</code> access in an IAM
         * user policy. Instead grant <code>Decrypt</code> access only in key policies. If
         * you must grant <code>Decrypt</code> access in an IAM user policy, you should
         * scope the resource to specific keys or to specific trusted accounts.</p> <p>The
         * result of this operation varies with the key state of the CMK. For details, see
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/Decrypt">AWS API
         * Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::DecryptOutcomeCallable DecryptCallable(const Model::DecryptRequest& request) const;

        /**
         * <p>Decrypts ciphertext. Ciphertext is plaintext that has been previously
         * encrypted by using any of the following operations:</p> <ul> <li> <p>
         * <a>GenerateDataKey</a> </p> </li> <li> <p>
         * <a>GenerateDataKeyWithoutPlaintext</a> </p> </li> <li> <p> <a>Encrypt</a> </p>
         * </li> </ul> <p>Note that if a caller has been granted access permissions to all
         * keys (through, for example, IAM user policies that grant <code>Decrypt</code>
         * permission on all resources), then ciphertext encrypted by using keys in other
         * accounts where the key grants access to the caller can be decrypted. To remedy
         * this, we recommend that you do not grant <code>Decrypt</code> access in an IAM
         * user policy. Instead grant <code>Decrypt</code> access only in key policies. If
         * you must grant <code>Decrypt</code> access in an IAM user policy, you should
         * scope the resource to specific keys or to specific trusted accounts.</p> <p>The
         * result of this operation varies with the key state of the CMK. For details, see
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/Decrypt">AWS API
         * Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void DecryptAsync(const Model::DecryptRequest& request, const DecryptResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Deletes the specified alias. You cannot perform this operation on an alias in
         * a different AWS account. </p> <p>Because an alias is not a property of a CMK,
         * you can delete and change the aliases of a CMK without affecting the CMK. Also,
         * aliases do not appear in the response from the <a>DescribeKey</a> operation. To
         * get the aliases of all CMKs, use the <a>ListAliases</a> operation. </p> <p>Each
         * CMK can have multiple aliases. To change the alias of a CMK, use
         * <a>DeleteAlias</a> to delete the current alias and <a>CreateAlias</a> to create
         * a new alias. To associate an existing alias with a different customer master key
         * (CMK), call <a>UpdateAlias</a>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DeleteAlias">AWS API
         * Reference</a></p>
         */
        virtual Model::DeleteAliasOutcome DeleteAlias(const Model::DeleteAliasRequest& request) const;

        /**
         * <p>Deletes the specified alias. You cannot perform this operation on an alias in
         * a different AWS account. </p> <p>Because an alias is not a property of a CMK,
         * you can delete and change the aliases of a CMK without affecting the CMK. Also,
         * aliases do not appear in the response from the <a>DescribeKey</a> operation. To
         * get the aliases of all CMKs, use the <a>ListAliases</a> operation. </p> <p>Each
         * CMK can have multiple aliases. To change the alias of a CMK, use
         * <a>DeleteAlias</a> to delete the current alias and <a>CreateAlias</a> to create
         * a new alias. To associate an existing alias with a different customer master key
         * (CMK), call <a>UpdateAlias</a>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DeleteAlias">AWS API
         * Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::DeleteAliasOutcomeCallable DeleteAliasCallable(const Model::DeleteAliasRequest& request) const;

        /**
         * <p>Deletes the specified alias. You cannot perform this operation on an alias in
         * a different AWS account. </p> <p>Because an alias is not a property of a CMK,
         * you can delete and change the aliases of a CMK without affecting the CMK. Also,
         * aliases do not appear in the response from the <a>DescribeKey</a> operation. To
         * get the aliases of all CMKs, use the <a>ListAliases</a> operation. </p> <p>Each
         * CMK can have multiple aliases. To change the alias of a CMK, use
         * <a>DeleteAlias</a> to delete the current alias and <a>CreateAlias</a> to create
         * a new alias. To associate an existing alias with a different customer master key
         * (CMK), call <a>UpdateAlias</a>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DeleteAlias">AWS API
         * Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void DeleteAliasAsync(const Model::DeleteAliasRequest& request, const DeleteAliasResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Deletes a <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a>. This operation does not delete the AWS CloudHSM cluster that is
         * associated with the custom key store, or affect any users or keys in the
         * cluster.</p> <p>The custom key store that you delete cannot contain any AWS KMS
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/concepts.html#master_keys">customer
         * master keys (CMKs)</a>. Before deleting the key store, verify that you will
         * never need to use any of the CMKs in the key store for any cryptographic
         * operations. Then, use <a>ScheduleKeyDeletion</a> to delete the AWS KMS customer
         * master keys (CMKs) from the key store. When the scheduled waiting period
         * expires, the <code>ScheduleKeyDeletion</code> operation deletes the CMKs. Then
         * it makes a best effort to delete the key material from the associated cluster.
         * However, you might need to manually <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/fix-keystore.html#fix-keystore-orphaned-key">delete
         * the orphaned key material</a> from the cluster and its backups.</p> <p>After all
         * CMKs are deleted from AWS KMS, use <a>DisconnectCustomKeyStore</a> to disconnect
         * the key store from AWS KMS. Then, you can delete the custom key store.</p>
         * <p>Instead of deleting the custom key store, consider using
         * <a>DisconnectCustomKeyStore</a> to disconnect it from AWS KMS. While the key
         * store is disconnected, you cannot create or use the CMKs in the key store. But,
         * you do not need to delete CMKs and you can reconnect a disconnected custom key
         * store at any time.</p> <p>If the operation succeeds, it returns a JSON object
         * with no properties.</p> <p>This operation is part of the <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/custom-key-store-overview.html">Custom
         * Key Store feature</a> feature in AWS KMS, which combines the convenience and
         * extensive integration of AWS KMS with the isolation and control of a
         * single-tenant key store.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DeleteCustomKeyStore">AWS
         * API Reference</a></p>
         */
        virtual Model::DeleteCustomKeyStoreOutcome DeleteCustomKeyStore(const Model::DeleteCustomKeyStoreRequest& request) const;

        /**
         * <p>Deletes a <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a>. This operation does not delete the AWS CloudHSM cluster that is
         * associated with the custom key store, or affect any users or keys in the
         * cluster.</p> <p>The custom key store that you delete cannot contain any AWS KMS
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/concepts.html#master_keys">customer
         * master keys (CMKs)</a>. Before deleting the key store, verify that you will
         * never need to use any of the CMKs in the key store for any cryptographic
         * operations. Then, use <a>ScheduleKeyDeletion</a> to delete the AWS KMS customer
         * master keys (CMKs) from the key store. When the scheduled waiting period
         * expires, the <code>ScheduleKeyDeletion</code> operation deletes the CMKs. Then
         * it makes a best effort to delete the key material from the associated cluster.
         * However, you might need to manually <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/fix-keystore.html#fix-keystore-orphaned-key">delete
         * the orphaned key material</a> from the cluster and its backups.</p> <p>After all
         * CMKs are deleted from AWS KMS, use <a>DisconnectCustomKeyStore</a> to disconnect
         * the key store from AWS KMS. Then, you can delete the custom key store.</p>
         * <p>Instead of deleting the custom key store, consider using
         * <a>DisconnectCustomKeyStore</a> to disconnect it from AWS KMS. While the key
         * store is disconnected, you cannot create or use the CMKs in the key store. But,
         * you do not need to delete CMKs and you can reconnect a disconnected custom key
         * store at any time.</p> <p>If the operation succeeds, it returns a JSON object
         * with no properties.</p> <p>This operation is part of the <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/custom-key-store-overview.html">Custom
         * Key Store feature</a> feature in AWS KMS, which combines the convenience and
         * extensive integration of AWS KMS with the isolation and control of a
         * single-tenant key store.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DeleteCustomKeyStore">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::DeleteCustomKeyStoreOutcomeCallable DeleteCustomKeyStoreCallable(const Model::DeleteCustomKeyStoreRequest& request) const;

        /**
         * <p>Deletes a <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a>. This operation does not delete the AWS CloudHSM cluster that is
         * associated with the custom key store, or affect any users or keys in the
         * cluster.</p> <p>The custom key store that you delete cannot contain any AWS KMS
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/concepts.html#master_keys">customer
         * master keys (CMKs)</a>. Before deleting the key store, verify that you will
         * never need to use any of the CMKs in the key store for any cryptographic
         * operations. Then, use <a>ScheduleKeyDeletion</a> to delete the AWS KMS customer
         * master keys (CMKs) from the key store. When the scheduled waiting period
         * expires, the <code>ScheduleKeyDeletion</code> operation deletes the CMKs. Then
         * it makes a best effort to delete the key material from the associated cluster.
         * However, you might need to manually <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/fix-keystore.html#fix-keystore-orphaned-key">delete
         * the orphaned key material</a> from the cluster and its backups.</p> <p>After all
         * CMKs are deleted from AWS KMS, use <a>DisconnectCustomKeyStore</a> to disconnect
         * the key store from AWS KMS. Then, you can delete the custom key store.</p>
         * <p>Instead of deleting the custom key store, consider using
         * <a>DisconnectCustomKeyStore</a> to disconnect it from AWS KMS. While the key
         * store is disconnected, you cannot create or use the CMKs in the key store. But,
         * you do not need to delete CMKs and you can reconnect a disconnected custom key
         * store at any time.</p> <p>If the operation succeeds, it returns a JSON object
         * with no properties.</p> <p>This operation is part of the <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/custom-key-store-overview.html">Custom
         * Key Store feature</a> feature in AWS KMS, which combines the convenience and
         * extensive integration of AWS KMS with the isolation and control of a
         * single-tenant key store.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DeleteCustomKeyStore">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void DeleteCustomKeyStoreAsync(const Model::DeleteCustomKeyStoreRequest& request, const DeleteCustomKeyStoreResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Deletes key material that you previously imported. This operation makes the
         * specified customer master key (CMK) unusable. For more information about
         * importing key material into AWS KMS, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/importing-keys.html">Importing
         * Key Material</a> in the <i>AWS Key Management Service Developer Guide</i>. You
         * cannot perform this operation on a CMK in a different AWS account.</p> <p>When
         * the specified CMK is in the <code>PendingDeletion</code> state, this operation
         * does not change the CMK's state. Otherwise, it changes the CMK's state to
         * <code>PendingImport</code>.</p> <p>After you delete key material, you can use
         * <a>ImportKeyMaterial</a> to reimport the same key material into the CMK.</p>
         * <p>The result of this operation varies with the key state of the CMK. For
         * details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DeleteImportedKeyMaterial">AWS
         * API Reference</a></p>
         */
        virtual Model::DeleteImportedKeyMaterialOutcome DeleteImportedKeyMaterial(const Model::DeleteImportedKeyMaterialRequest& request) const;

        /**
         * <p>Deletes key material that you previously imported. This operation makes the
         * specified customer master key (CMK) unusable. For more information about
         * importing key material into AWS KMS, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/importing-keys.html">Importing
         * Key Material</a> in the <i>AWS Key Management Service Developer Guide</i>. You
         * cannot perform this operation on a CMK in a different AWS account.</p> <p>When
         * the specified CMK is in the <code>PendingDeletion</code> state, this operation
         * does not change the CMK's state. Otherwise, it changes the CMK's state to
         * <code>PendingImport</code>.</p> <p>After you delete key material, you can use
         * <a>ImportKeyMaterial</a> to reimport the same key material into the CMK.</p>
         * <p>The result of this operation varies with the key state of the CMK. For
         * details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DeleteImportedKeyMaterial">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::DeleteImportedKeyMaterialOutcomeCallable DeleteImportedKeyMaterialCallable(const Model::DeleteImportedKeyMaterialRequest& request) const;

        /**
         * <p>Deletes key material that you previously imported. This operation makes the
         * specified customer master key (CMK) unusable. For more information about
         * importing key material into AWS KMS, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/importing-keys.html">Importing
         * Key Material</a> in the <i>AWS Key Management Service Developer Guide</i>. You
         * cannot perform this operation on a CMK in a different AWS account.</p> <p>When
         * the specified CMK is in the <code>PendingDeletion</code> state, this operation
         * does not change the CMK's state. Otherwise, it changes the CMK's state to
         * <code>PendingImport</code>.</p> <p>After you delete key material, you can use
         * <a>ImportKeyMaterial</a> to reimport the same key material into the CMK.</p>
         * <p>The result of this operation varies with the key state of the CMK. For
         * details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DeleteImportedKeyMaterial">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void DeleteImportedKeyMaterialAsync(const Model::DeleteImportedKeyMaterialRequest& request, const DeleteImportedKeyMaterialResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Gets information about <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key stores</a> in the account and region.</p> <p>This operation is part of the
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/custom-key-store-overview.html">Custom
         * Key Store feature</a> feature in AWS KMS, which combines the convenience and
         * extensive integration of AWS KMS with the isolation and control of a
         * single-tenant key store.</p> <p>By default, this operation returns information
         * about all custom key stores in the account and region. To get only information
         * about a particular custom key store, use either the
         * <code>CustomKeyStoreName</code> or <code>CustomKeyStoreId</code> parameter (but
         * not both).</p> <p>To determine whether the custom key store is connected to its
         * AWS CloudHSM cluster, use the <code>ConnectionState</code> element in the
         * response. If an attempt to connect the custom key store failed, the
         * <code>ConnectionState</code> value is <code>FAILED</code> and the
         * <code>ConnectionErrorCode</code> element in the response indicates the cause of
         * the failure. For help interpreting the <code>ConnectionErrorCode</code>, see
         * <a>CustomKeyStoresListEntry</a>.</p> <p>Custom key stores have a
         * <code>DISCONNECTED</code> connection state if the key store has never been
         * connected or you use the <a>DisconnectCustomKeyStore</a> operation to disconnect
         * it. If your custom key store state is <code>CONNECTED</code> but you are having
         * trouble using it, make sure that its associated AWS CloudHSM cluster is active
         * and contains the minimum number of HSMs required for the operation, if any.</p>
         * <p> For help repairing your custom key store, see the <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/fix-keystore-html">Troubleshooting
         * Custom Key Stores</a> topic in the <i>AWS Key Management Service Developer
         * Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DescribeCustomKeyStores">AWS
         * API Reference</a></p>
         */
        virtual Model::DescribeCustomKeyStoresOutcome DescribeCustomKeyStores(const Model::DescribeCustomKeyStoresRequest& request) const;

        /**
         * <p>Gets information about <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key stores</a> in the account and region.</p> <p>This operation is part of the
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/custom-key-store-overview.html">Custom
         * Key Store feature</a> feature in AWS KMS, which combines the convenience and
         * extensive integration of AWS KMS with the isolation and control of a
         * single-tenant key store.</p> <p>By default, this operation returns information
         * about all custom key stores in the account and region. To get only information
         * about a particular custom key store, use either the
         * <code>CustomKeyStoreName</code> or <code>CustomKeyStoreId</code> parameter (but
         * not both).</p> <p>To determine whether the custom key store is connected to its
         * AWS CloudHSM cluster, use the <code>ConnectionState</code> element in the
         * response. If an attempt to connect the custom key store failed, the
         * <code>ConnectionState</code> value is <code>FAILED</code> and the
         * <code>ConnectionErrorCode</code> element in the response indicates the cause of
         * the failure. For help interpreting the <code>ConnectionErrorCode</code>, see
         * <a>CustomKeyStoresListEntry</a>.</p> <p>Custom key stores have a
         * <code>DISCONNECTED</code> connection state if the key store has never been
         * connected or you use the <a>DisconnectCustomKeyStore</a> operation to disconnect
         * it. If your custom key store state is <code>CONNECTED</code> but you are having
         * trouble using it, make sure that its associated AWS CloudHSM cluster is active
         * and contains the minimum number of HSMs required for the operation, if any.</p>
         * <p> For help repairing your custom key store, see the <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/fix-keystore-html">Troubleshooting
         * Custom Key Stores</a> topic in the <i>AWS Key Management Service Developer
         * Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DescribeCustomKeyStores">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::DescribeCustomKeyStoresOutcomeCallable DescribeCustomKeyStoresCallable(const Model::DescribeCustomKeyStoresRequest& request) const;

        /**
         * <p>Gets information about <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key stores</a> in the account and region.</p> <p>This operation is part of the
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/custom-key-store-overview.html">Custom
         * Key Store feature</a> feature in AWS KMS, which combines the convenience and
         * extensive integration of AWS KMS with the isolation and control of a
         * single-tenant key store.</p> <p>By default, this operation returns information
         * about all custom key stores in the account and region. To get only information
         * about a particular custom key store, use either the
         * <code>CustomKeyStoreName</code> or <code>CustomKeyStoreId</code> parameter (but
         * not both).</p> <p>To determine whether the custom key store is connected to its
         * AWS CloudHSM cluster, use the <code>ConnectionState</code> element in the
         * response. If an attempt to connect the custom key store failed, the
         * <code>ConnectionState</code> value is <code>FAILED</code> and the
         * <code>ConnectionErrorCode</code> element in the response indicates the cause of
         * the failure. For help interpreting the <code>ConnectionErrorCode</code>, see
         * <a>CustomKeyStoresListEntry</a>.</p> <p>Custom key stores have a
         * <code>DISCONNECTED</code> connection state if the key store has never been
         * connected or you use the <a>DisconnectCustomKeyStore</a> operation to disconnect
         * it. If your custom key store state is <code>CONNECTED</code> but you are having
         * trouble using it, make sure that its associated AWS CloudHSM cluster is active
         * and contains the minimum number of HSMs required for the operation, if any.</p>
         * <p> For help repairing your custom key store, see the <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/fix-keystore-html">Troubleshooting
         * Custom Key Stores</a> topic in the <i>AWS Key Management Service Developer
         * Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DescribeCustomKeyStores">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void DescribeCustomKeyStoresAsync(const Model::DescribeCustomKeyStoresRequest& request, const DescribeCustomKeyStoresResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Provides detailed information about the specified customer master key
         * (CMK).</p> <p>If you use <code>DescribeKey</code> on a predefined AWS alias,
         * that is, an AWS alias with no key ID, AWS KMS associates the alias with an <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/concepts.html#master_keys">AWS
         * managed CMK</a> and returns its <code>KeyId</code> and <code>Arn</code> in the
         * response.</p> <p>To perform this operation on a CMK in a different AWS account,
         * specify the key ARN or alias ARN in the value of the KeyId
         * parameter.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DescribeKey">AWS API
         * Reference</a></p>
         */
        virtual Model::DescribeKeyOutcome DescribeKey(const Model::DescribeKeyRequest& request) const;

        /**
         * <p>Provides detailed information about the specified customer master key
         * (CMK).</p> <p>If you use <code>DescribeKey</code> on a predefined AWS alias,
         * that is, an AWS alias with no key ID, AWS KMS associates the alias with an <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/concepts.html#master_keys">AWS
         * managed CMK</a> and returns its <code>KeyId</code> and <code>Arn</code> in the
         * response.</p> <p>To perform this operation on a CMK in a different AWS account,
         * specify the key ARN or alias ARN in the value of the KeyId
         * parameter.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DescribeKey">AWS API
         * Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::DescribeKeyOutcomeCallable DescribeKeyCallable(const Model::DescribeKeyRequest& request) const;

        /**
         * <p>Provides detailed information about the specified customer master key
         * (CMK).</p> <p>If you use <code>DescribeKey</code> on a predefined AWS alias,
         * that is, an AWS alias with no key ID, AWS KMS associates the alias with an <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/concepts.html#master_keys">AWS
         * managed CMK</a> and returns its <code>KeyId</code> and <code>Arn</code> in the
         * response.</p> <p>To perform this operation on a CMK in a different AWS account,
         * specify the key ARN or alias ARN in the value of the KeyId
         * parameter.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DescribeKey">AWS API
         * Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void DescribeKeyAsync(const Model::DescribeKeyRequest& request, const DescribeKeyResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Sets the state of a customer master key (CMK) to disabled, thereby preventing
         * its use for cryptographic operations. You cannot perform this operation on a CMK
         * in a different AWS account.</p> <p>For more information about how key state
         * affects the use of a CMK, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects the Use of a Customer Master Key</a> in the <i>AWS Key
         * Management Service Developer Guide</i>.</p> <p>The result of this operation
         * varies with the key state of the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DisableKey">AWS API
         * Reference</a></p>
         */
        virtual Model::DisableKeyOutcome DisableKey(const Model::DisableKeyRequest& request) const;

        /**
         * <p>Sets the state of a customer master key (CMK) to disabled, thereby preventing
         * its use for cryptographic operations. You cannot perform this operation on a CMK
         * in a different AWS account.</p> <p>For more information about how key state
         * affects the use of a CMK, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects the Use of a Customer Master Key</a> in the <i>AWS Key
         * Management Service Developer Guide</i>.</p> <p>The result of this operation
         * varies with the key state of the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DisableKey">AWS API
         * Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::DisableKeyOutcomeCallable DisableKeyCallable(const Model::DisableKeyRequest& request) const;

        /**
         * <p>Sets the state of a customer master key (CMK) to disabled, thereby preventing
         * its use for cryptographic operations. You cannot perform this operation on a CMK
         * in a different AWS account.</p> <p>For more information about how key state
         * affects the use of a CMK, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects the Use of a Customer Master Key</a> in the <i>AWS Key
         * Management Service Developer Guide</i>.</p> <p>The result of this operation
         * varies with the key state of the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DisableKey">AWS API
         * Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void DisableKeyAsync(const Model::DisableKeyRequest& request, const DisableKeyResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Disables <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/rotate-keys.html">automatic
         * rotation of the key material</a> for the specified customer master key (CMK).
         * You cannot perform this operation on a CMK in a different AWS account.</p>
         * <p>The result of this operation varies with the key state of the CMK. For
         * details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DisableKeyRotation">AWS
         * API Reference</a></p>
         */
        virtual Model::DisableKeyRotationOutcome DisableKeyRotation(const Model::DisableKeyRotationRequest& request) const;

        /**
         * <p>Disables <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/rotate-keys.html">automatic
         * rotation of the key material</a> for the specified customer master key (CMK).
         * You cannot perform this operation on a CMK in a different AWS account.</p>
         * <p>The result of this operation varies with the key state of the CMK. For
         * details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DisableKeyRotation">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::DisableKeyRotationOutcomeCallable DisableKeyRotationCallable(const Model::DisableKeyRotationRequest& request) const;

        /**
         * <p>Disables <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/rotate-keys.html">automatic
         * rotation of the key material</a> for the specified customer master key (CMK).
         * You cannot perform this operation on a CMK in a different AWS account.</p>
         * <p>The result of this operation varies with the key state of the CMK. For
         * details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DisableKeyRotation">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void DisableKeyRotationAsync(const Model::DisableKeyRotationRequest& request, const DisableKeyRotationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Disconnects the <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a> from its associated AWS CloudHSM cluster. While a custom key store
         * is disconnected, you can manage the custom key store and its customer master
         * keys (CMKs), but you cannot create or use CMKs in the custom key store. You can
         * reconnect the custom key store at any time.</p> <note> <p>While a custom key
         * store is disconnected, all attempts to create customer master keys (CMKs) in the
         * custom key store or to use existing CMKs in cryptographic operations will fail.
         * This action can prevent users from storing and accessing sensitive data.</p>
         * </note> <p/> <p>To find the connection state of a custom key store, use the
         * <a>DescribeCustomKeyStores</a> operation. To reconnect a custom key store, use
         * the <a>ConnectCustomKeyStore</a> operation.</p> <p>If the operation succeeds, it
         * returns a JSON object with no properties.</p> <p>This operation is part of the
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/custom-key-store-overview.html">Custom
         * Key Store feature</a> feature in AWS KMS, which combines the convenience and
         * extensive integration of AWS KMS with the isolation and control of a
         * single-tenant key store.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DisconnectCustomKeyStore">AWS
         * API Reference</a></p>
         */
        virtual Model::DisconnectCustomKeyStoreOutcome DisconnectCustomKeyStore(const Model::DisconnectCustomKeyStoreRequest& request) const;

        /**
         * <p>Disconnects the <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a> from its associated AWS CloudHSM cluster. While a custom key store
         * is disconnected, you can manage the custom key store and its customer master
         * keys (CMKs), but you cannot create or use CMKs in the custom key store. You can
         * reconnect the custom key store at any time.</p> <note> <p>While a custom key
         * store is disconnected, all attempts to create customer master keys (CMKs) in the
         * custom key store or to use existing CMKs in cryptographic operations will fail.
         * This action can prevent users from storing and accessing sensitive data.</p>
         * </note> <p/> <p>To find the connection state of a custom key store, use the
         * <a>DescribeCustomKeyStores</a> operation. To reconnect a custom key store, use
         * the <a>ConnectCustomKeyStore</a> operation.</p> <p>If the operation succeeds, it
         * returns a JSON object with no properties.</p> <p>This operation is part of the
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/custom-key-store-overview.html">Custom
         * Key Store feature</a> feature in AWS KMS, which combines the convenience and
         * extensive integration of AWS KMS with the isolation and control of a
         * single-tenant key store.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DisconnectCustomKeyStore">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::DisconnectCustomKeyStoreOutcomeCallable DisconnectCustomKeyStoreCallable(const Model::DisconnectCustomKeyStoreRequest& request) const;

        /**
         * <p>Disconnects the <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a> from its associated AWS CloudHSM cluster. While a custom key store
         * is disconnected, you can manage the custom key store and its customer master
         * keys (CMKs), but you cannot create or use CMKs in the custom key store. You can
         * reconnect the custom key store at any time.</p> <note> <p>While a custom key
         * store is disconnected, all attempts to create customer master keys (CMKs) in the
         * custom key store or to use existing CMKs in cryptographic operations will fail.
         * This action can prevent users from storing and accessing sensitive data.</p>
         * </note> <p/> <p>To find the connection state of a custom key store, use the
         * <a>DescribeCustomKeyStores</a> operation. To reconnect a custom key store, use
         * the <a>ConnectCustomKeyStore</a> operation.</p> <p>If the operation succeeds, it
         * returns a JSON object with no properties.</p> <p>This operation is part of the
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/custom-key-store-overview.html">Custom
         * Key Store feature</a> feature in AWS KMS, which combines the convenience and
         * extensive integration of AWS KMS with the isolation and control of a
         * single-tenant key store.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/DisconnectCustomKeyStore">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void DisconnectCustomKeyStoreAsync(const Model::DisconnectCustomKeyStoreRequest& request, const DisconnectCustomKeyStoreResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Sets the key state of a customer master key (CMK) to enabled. This allows you
         * to use the CMK for cryptographic operations. You cannot perform this operation
         * on a CMK in a different AWS account.</p> <p>The result of this operation varies
         * with the key state of the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/EnableKey">AWS API
         * Reference</a></p>
         */
        virtual Model::EnableKeyOutcome EnableKey(const Model::EnableKeyRequest& request) const;

        /**
         * <p>Sets the key state of a customer master key (CMK) to enabled. This allows you
         * to use the CMK for cryptographic operations. You cannot perform this operation
         * on a CMK in a different AWS account.</p> <p>The result of this operation varies
         * with the key state of the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/EnableKey">AWS API
         * Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::EnableKeyOutcomeCallable EnableKeyCallable(const Model::EnableKeyRequest& request) const;

        /**
         * <p>Sets the key state of a customer master key (CMK) to enabled. This allows you
         * to use the CMK for cryptographic operations. You cannot perform this operation
         * on a CMK in a different AWS account.</p> <p>The result of this operation varies
         * with the key state of the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/EnableKey">AWS API
         * Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void EnableKeyAsync(const Model::EnableKeyRequest& request, const EnableKeyResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Enables <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/rotate-keys.html">automatic
         * rotation of the key material</a> for the specified customer master key (CMK).
         * You cannot perform this operation on a CMK in a different AWS account.</p>
         * <p>You cannot enable automatic rotation of CMKs with imported key material or
         * CMKs in a <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a>.</p> <p>The result of this operation varies with the key state of
         * the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/EnableKeyRotation">AWS
         * API Reference</a></p>
         */
        virtual Model::EnableKeyRotationOutcome EnableKeyRotation(const Model::EnableKeyRotationRequest& request) const;

        /**
         * <p>Enables <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/rotate-keys.html">automatic
         * rotation of the key material</a> for the specified customer master key (CMK).
         * You cannot perform this operation on a CMK in a different AWS account.</p>
         * <p>You cannot enable automatic rotation of CMKs with imported key material or
         * CMKs in a <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a>.</p> <p>The result of this operation varies with the key state of
         * the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/EnableKeyRotation">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::EnableKeyRotationOutcomeCallable EnableKeyRotationCallable(const Model::EnableKeyRotationRequest& request) const;

        /**
         * <p>Enables <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/rotate-keys.html">automatic
         * rotation of the key material</a> for the specified customer master key (CMK).
         * You cannot perform this operation on a CMK in a different AWS account.</p>
         * <p>You cannot enable automatic rotation of CMKs with imported key material or
         * CMKs in a <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a>.</p> <p>The result of this operation varies with the key state of
         * the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/EnableKeyRotation">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void EnableKeyRotationAsync(const Model::EnableKeyRotationRequest& request, const EnableKeyRotationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Encrypts plaintext into ciphertext by using a customer master key (CMK). The
         * <code>Encrypt</code> operation has two primary use cases:</p> <ul> <li> <p>You
         * can encrypt up to 4 kilobytes (4096 bytes) of arbitrary data such as an RSA key,
         * a database password, or other sensitive information.</p> </li> <li> <p>To move
         * encrypted data from one AWS region to another, you can use this operation to
         * encrypt in the new region the plaintext data key that was used to encrypt the
         * data in the original region. This provides you with an encrypted copy of the
         * data key that can be decrypted in the new region and used there to decrypt the
         * encrypted data.</p> </li> </ul> <p>To perform this operation on a CMK in a
         * different AWS account, specify the key ARN or alias ARN in the value of the
         * KeyId parameter.</p> <p>Unless you are moving encrypted data from one region to
         * another, you don't use this operation to encrypt a generated data key within a
         * region. To get data keys that are already encrypted, call the
         * <a>GenerateDataKey</a> or <a>GenerateDataKeyWithoutPlaintext</a> operation. Data
         * keys don't need to be encrypted again by calling <code>Encrypt</code>.</p> <p>To
         * encrypt data locally in your application, use the <a>GenerateDataKey</a>
         * operation to return a plaintext data encryption key and a copy of the key
         * encrypted under the CMK of your choosing.</p> <p>The result of this operation
         * varies with the key state of the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/Encrypt">AWS API
         * Reference</a></p>
         */
        virtual Model::EncryptOutcome Encrypt(const Model::EncryptRequest& request) const;

        /**
         * <p>Encrypts plaintext into ciphertext by using a customer master key (CMK). The
         * <code>Encrypt</code> operation has two primary use cases:</p> <ul> <li> <p>You
         * can encrypt up to 4 kilobytes (4096 bytes) of arbitrary data such as an RSA key,
         * a database password, or other sensitive information.</p> </li> <li> <p>To move
         * encrypted data from one AWS region to another, you can use this operation to
         * encrypt in the new region the plaintext data key that was used to encrypt the
         * data in the original region. This provides you with an encrypted copy of the
         * data key that can be decrypted in the new region and used there to decrypt the
         * encrypted data.</p> </li> </ul> <p>To perform this operation on a CMK in a
         * different AWS account, specify the key ARN or alias ARN in the value of the
         * KeyId parameter.</p> <p>Unless you are moving encrypted data from one region to
         * another, you don't use this operation to encrypt a generated data key within a
         * region. To get data keys that are already encrypted, call the
         * <a>GenerateDataKey</a> or <a>GenerateDataKeyWithoutPlaintext</a> operation. Data
         * keys don't need to be encrypted again by calling <code>Encrypt</code>.</p> <p>To
         * encrypt data locally in your application, use the <a>GenerateDataKey</a>
         * operation to return a plaintext data encryption key and a copy of the key
         * encrypted under the CMK of your choosing.</p> <p>The result of this operation
         * varies with the key state of the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/Encrypt">AWS API
         * Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::EncryptOutcomeCallable EncryptCallable(const Model::EncryptRequest& request) const;

        /**
         * <p>Encrypts plaintext into ciphertext by using a customer master key (CMK). The
         * <code>Encrypt</code> operation has two primary use cases:</p> <ul> <li> <p>You
         * can encrypt up to 4 kilobytes (4096 bytes) of arbitrary data such as an RSA key,
         * a database password, or other sensitive information.</p> </li> <li> <p>To move
         * encrypted data from one AWS region to another, you can use this operation to
         * encrypt in the new region the plaintext data key that was used to encrypt the
         * data in the original region. This provides you with an encrypted copy of the
         * data key that can be decrypted in the new region and used there to decrypt the
         * encrypted data.</p> </li> </ul> <p>To perform this operation on a CMK in a
         * different AWS account, specify the key ARN or alias ARN in the value of the
         * KeyId parameter.</p> <p>Unless you are moving encrypted data from one region to
         * another, you don't use this operation to encrypt a generated data key within a
         * region. To get data keys that are already encrypted, call the
         * <a>GenerateDataKey</a> or <a>GenerateDataKeyWithoutPlaintext</a> operation. Data
         * keys don't need to be encrypted again by calling <code>Encrypt</code>.</p> <p>To
         * encrypt data locally in your application, use the <a>GenerateDataKey</a>
         * operation to return a plaintext data encryption key and a copy of the key
         * encrypted under the CMK of your choosing.</p> <p>The result of this operation
         * varies with the key state of the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/Encrypt">AWS API
         * Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void EncryptAsync(const Model::EncryptRequest& request, const EncryptResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Returns a data encryption key that you can use in your application to encrypt
         * data locally. </p> <p>You must specify the customer master key (CMK) under which
         * to generate the data key. You must also specify the length of the data key using
         * either the <code>KeySpec</code> or <code>NumberOfBytes</code> field. You must
         * specify one field or the other, but not both. For common key lengths (128-bit
         * and 256-bit symmetric keys), we recommend that you use <code>KeySpec</code>. To
         * perform this operation on a CMK in a different AWS account, specify the key ARN
         * or alias ARN in the value of the KeyId parameter.</p> <p>This operation returns
         * a plaintext copy of the data key in the <code>Plaintext</code> field of the
         * response, and an encrypted copy of the data key in the
         * <code>CiphertextBlob</code> field. The data key is encrypted under the CMK
         * specified in the <code>KeyId</code> field of the request. </p> <p>We recommend
         * that you use the following pattern to encrypt data locally in your
         * application:</p> <ol> <li> <p>Use this operation (<code>GenerateDataKey</code>)
         * to get a data encryption key.</p> </li> <li> <p>Use the plaintext data
         * encryption key (returned in the <code>Plaintext</code> field of the response) to
         * encrypt data locally, then erase the plaintext data key from memory.</p> </li>
         * <li> <p>Store the encrypted data key (returned in the
         * <code>CiphertextBlob</code> field of the response) alongside the locally
         * encrypted data.</p> </li> </ol> <p>To decrypt data locally:</p> <ol> <li> <p>Use
         * the <a>Decrypt</a> operation to decrypt the encrypted data key into a plaintext
         * copy of the data key.</p> </li> <li> <p>Use the plaintext data key to decrypt
         * data locally, then erase the plaintext data key from memory.</p> </li> </ol>
         * <p>To return only an encrypted copy of the data key, use
         * <a>GenerateDataKeyWithoutPlaintext</a>. To return a random byte string that is
         * cryptographically secure, use <a>GenerateRandom</a>.</p> <p>If you use the
         * optional <code>EncryptionContext</code> field, you must store at least enough
         * information to be able to reconstruct the full encryption context when you later
         * send the ciphertext to the <a>Decrypt</a> operation. It is a good practice to
         * choose an encryption context that you can reconstruct on the fly to better
         * secure the ciphertext. For more information, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/encryption-context.html">Encryption
         * Context</a> in the <i>AWS Key Management Service Developer Guide</i>.</p> <p>The
         * result of this operation varies with the key state of the CMK. For details, see
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/GenerateDataKey">AWS
         * API Reference</a></p>
         */
        virtual Model::GenerateDataKeyOutcome GenerateDataKey(const Model::GenerateDataKeyRequest& request) const;

        /**
         * <p>Returns a data encryption key that you can use in your application to encrypt
         * data locally. </p> <p>You must specify the customer master key (CMK) under which
         * to generate the data key. You must also specify the length of the data key using
         * either the <code>KeySpec</code> or <code>NumberOfBytes</code> field. You must
         * specify one field or the other, but not both. For common key lengths (128-bit
         * and 256-bit symmetric keys), we recommend that you use <code>KeySpec</code>. To
         * perform this operation on a CMK in a different AWS account, specify the key ARN
         * or alias ARN in the value of the KeyId parameter.</p> <p>This operation returns
         * a plaintext copy of the data key in the <code>Plaintext</code> field of the
         * response, and an encrypted copy of the data key in the
         * <code>CiphertextBlob</code> field. The data key is encrypted under the CMK
         * specified in the <code>KeyId</code> field of the request. </p> <p>We recommend
         * that you use the following pattern to encrypt data locally in your
         * application:</p> <ol> <li> <p>Use this operation (<code>GenerateDataKey</code>)
         * to get a data encryption key.</p> </li> <li> <p>Use the plaintext data
         * encryption key (returned in the <code>Plaintext</code> field of the response) to
         * encrypt data locally, then erase the plaintext data key from memory.</p> </li>
         * <li> <p>Store the encrypted data key (returned in the
         * <code>CiphertextBlob</code> field of the response) alongside the locally
         * encrypted data.</p> </li> </ol> <p>To decrypt data locally:</p> <ol> <li> <p>Use
         * the <a>Decrypt</a> operation to decrypt the encrypted data key into a plaintext
         * copy of the data key.</p> </li> <li> <p>Use the plaintext data key to decrypt
         * data locally, then erase the plaintext data key from memory.</p> </li> </ol>
         * <p>To return only an encrypted copy of the data key, use
         * <a>GenerateDataKeyWithoutPlaintext</a>. To return a random byte string that is
         * cryptographically secure, use <a>GenerateRandom</a>.</p> <p>If you use the
         * optional <code>EncryptionContext</code> field, you must store at least enough
         * information to be able to reconstruct the full encryption context when you later
         * send the ciphertext to the <a>Decrypt</a> operation. It is a good practice to
         * choose an encryption context that you can reconstruct on the fly to better
         * secure the ciphertext. For more information, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/encryption-context.html">Encryption
         * Context</a> in the <i>AWS Key Management Service Developer Guide</i>.</p> <p>The
         * result of this operation varies with the key state of the CMK. For details, see
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/GenerateDataKey">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::GenerateDataKeyOutcomeCallable GenerateDataKeyCallable(const Model::GenerateDataKeyRequest& request) const;

        /**
         * <p>Returns a data encryption key that you can use in your application to encrypt
         * data locally. </p> <p>You must specify the customer master key (CMK) under which
         * to generate the data key. You must also specify the length of the data key using
         * either the <code>KeySpec</code> or <code>NumberOfBytes</code> field. You must
         * specify one field or the other, but not both. For common key lengths (128-bit
         * and 256-bit symmetric keys), we recommend that you use <code>KeySpec</code>. To
         * perform this operation on a CMK in a different AWS account, specify the key ARN
         * or alias ARN in the value of the KeyId parameter.</p> <p>This operation returns
         * a plaintext copy of the data key in the <code>Plaintext</code> field of the
         * response, and an encrypted copy of the data key in the
         * <code>CiphertextBlob</code> field. The data key is encrypted under the CMK
         * specified in the <code>KeyId</code> field of the request. </p> <p>We recommend
         * that you use the following pattern to encrypt data locally in your
         * application:</p> <ol> <li> <p>Use this operation (<code>GenerateDataKey</code>)
         * to get a data encryption key.</p> </li> <li> <p>Use the plaintext data
         * encryption key (returned in the <code>Plaintext</code> field of the response) to
         * encrypt data locally, then erase the plaintext data key from memory.</p> </li>
         * <li> <p>Store the encrypted data key (returned in the
         * <code>CiphertextBlob</code> field of the response) alongside the locally
         * encrypted data.</p> </li> </ol> <p>To decrypt data locally:</p> <ol> <li> <p>Use
         * the <a>Decrypt</a> operation to decrypt the encrypted data key into a plaintext
         * copy of the data key.</p> </li> <li> <p>Use the plaintext data key to decrypt
         * data locally, then erase the plaintext data key from memory.</p> </li> </ol>
         * <p>To return only an encrypted copy of the data key, use
         * <a>GenerateDataKeyWithoutPlaintext</a>. To return a random byte string that is
         * cryptographically secure, use <a>GenerateRandom</a>.</p> <p>If you use the
         * optional <code>EncryptionContext</code> field, you must store at least enough
         * information to be able to reconstruct the full encryption context when you later
         * send the ciphertext to the <a>Decrypt</a> operation. It is a good practice to
         * choose an encryption context that you can reconstruct on the fly to better
         * secure the ciphertext. For more information, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/encryption-context.html">Encryption
         * Context</a> in the <i>AWS Key Management Service Developer Guide</i>.</p> <p>The
         * result of this operation varies with the key state of the CMK. For details, see
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/GenerateDataKey">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void GenerateDataKeyAsync(const Model::GenerateDataKeyRequest& request, const GenerateDataKeyResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Returns a data encryption key encrypted under a customer master key (CMK).
         * This operation is identical to <a>GenerateDataKey</a> but returns only the
         * encrypted copy of the data key. </p> <p>To perform this operation on a CMK in a
         * different AWS account, specify the key ARN or alias ARN in the value of the
         * KeyId parameter.</p> <p>This operation is useful in a system that has multiple
         * components with different degrees of trust. For example, consider a system that
         * stores encrypted data in containers. Each container stores the encrypted data
         * and an encrypted copy of the data key. One component of the system, called the
         * <i>control plane</i>, creates new containers. When it creates a new container,
         * it uses this operation (<code>GenerateDataKeyWithoutPlaintext</code>) to get an
         * encrypted data key and then stores it in the container. Later, a different
         * component of the system, called the <i>data plane</i>, puts encrypted data into
         * the containers. To do this, it passes the encrypted data key to the
         * <a>Decrypt</a> operation, then uses the returned plaintext data key to encrypt
         * data, and finally stores the encrypted data in the container. In this system,
         * the control plane never sees the plaintext data key.</p> <p>The result of this
         * operation varies with the key state of the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/GenerateDataKeyWithoutPlaintext">AWS
         * API Reference</a></p>
         */
        virtual Model::GenerateDataKeyWithoutPlaintextOutcome GenerateDataKeyWithoutPlaintext(const Model::GenerateDataKeyWithoutPlaintextRequest& request) const;

        /**
         * <p>Returns a data encryption key encrypted under a customer master key (CMK).
         * This operation is identical to <a>GenerateDataKey</a> but returns only the
         * encrypted copy of the data key. </p> <p>To perform this operation on a CMK in a
         * different AWS account, specify the key ARN or alias ARN in the value of the
         * KeyId parameter.</p> <p>This operation is useful in a system that has multiple
         * components with different degrees of trust. For example, consider a system that
         * stores encrypted data in containers. Each container stores the encrypted data
         * and an encrypted copy of the data key. One component of the system, called the
         * <i>control plane</i>, creates new containers. When it creates a new container,
         * it uses this operation (<code>GenerateDataKeyWithoutPlaintext</code>) to get an
         * encrypted data key and then stores it in the container. Later, a different
         * component of the system, called the <i>data plane</i>, puts encrypted data into
         * the containers. To do this, it passes the encrypted data key to the
         * <a>Decrypt</a> operation, then uses the returned plaintext data key to encrypt
         * data, and finally stores the encrypted data in the container. In this system,
         * the control plane never sees the plaintext data key.</p> <p>The result of this
         * operation varies with the key state of the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/GenerateDataKeyWithoutPlaintext">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::GenerateDataKeyWithoutPlaintextOutcomeCallable GenerateDataKeyWithoutPlaintextCallable(const Model::GenerateDataKeyWithoutPlaintextRequest& request) const;

        /**
         * <p>Returns a data encryption key encrypted under a customer master key (CMK).
         * This operation is identical to <a>GenerateDataKey</a> but returns only the
         * encrypted copy of the data key. </p> <p>To perform this operation on a CMK in a
         * different AWS account, specify the key ARN or alias ARN in the value of the
         * KeyId parameter.</p> <p>This operation is useful in a system that has multiple
         * components with different degrees of trust. For example, consider a system that
         * stores encrypted data in containers. Each container stores the encrypted data
         * and an encrypted copy of the data key. One component of the system, called the
         * <i>control plane</i>, creates new containers. When it creates a new container,
         * it uses this operation (<code>GenerateDataKeyWithoutPlaintext</code>) to get an
         * encrypted data key and then stores it in the container. Later, a different
         * component of the system, called the <i>data plane</i>, puts encrypted data into
         * the containers. To do this, it passes the encrypted data key to the
         * <a>Decrypt</a> operation, then uses the returned plaintext data key to encrypt
         * data, and finally stores the encrypted data in the container. In this system,
         * the control plane never sees the plaintext data key.</p> <p>The result of this
         * operation varies with the key state of the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/GenerateDataKeyWithoutPlaintext">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void GenerateDataKeyWithoutPlaintextAsync(const Model::GenerateDataKeyWithoutPlaintextRequest& request, const GenerateDataKeyWithoutPlaintextResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Returns a random byte string that is cryptographically secure.</p> <p>By
         * default, the random byte string is generated in AWS KMS. To generate the byte
         * string in the AWS CloudHSM cluster that is associated with a <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a>, specify the custom key store ID.</p> <p>For more information
         * about entropy and random number generation, see the <a
         * href="https://d0.awsstatic.com/whitepapers/KMS-Cryptographic-Details.pdf">AWS
         * Key Management Service Cryptographic Details</a> whitepaper.</p><p><h3>See
         * Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/GenerateRandom">AWS
         * API Reference</a></p>
         */
        virtual Model::GenerateRandomOutcome GenerateRandom(const Model::GenerateRandomRequest& request) const;

        /**
         * <p>Returns a random byte string that is cryptographically secure.</p> <p>By
         * default, the random byte string is generated in AWS KMS. To generate the byte
         * string in the AWS CloudHSM cluster that is associated with a <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a>, specify the custom key store ID.</p> <p>For more information
         * about entropy and random number generation, see the <a
         * href="https://d0.awsstatic.com/whitepapers/KMS-Cryptographic-Details.pdf">AWS
         * Key Management Service Cryptographic Details</a> whitepaper.</p><p><h3>See
         * Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/GenerateRandom">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::GenerateRandomOutcomeCallable GenerateRandomCallable(const Model::GenerateRandomRequest& request) const;

        /**
         * <p>Returns a random byte string that is cryptographically secure.</p> <p>By
         * default, the random byte string is generated in AWS KMS. To generate the byte
         * string in the AWS CloudHSM cluster that is associated with a <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a>, specify the custom key store ID.</p> <p>For more information
         * about entropy and random number generation, see the <a
         * href="https://d0.awsstatic.com/whitepapers/KMS-Cryptographic-Details.pdf">AWS
         * Key Management Service Cryptographic Details</a> whitepaper.</p><p><h3>See
         * Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/GenerateRandom">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void GenerateRandomAsync(const Model::GenerateRandomRequest& request, const GenerateRandomResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Gets a key policy attached to the specified customer master key (CMK). You
         * cannot perform this operation on a CMK in a different AWS account.</p><p><h3>See
         * Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/GetKeyPolicy">AWS
         * API Reference</a></p>
         */
        virtual Model::GetKeyPolicyOutcome GetKeyPolicy(const Model::GetKeyPolicyRequest& request) const;

        /**
         * <p>Gets a key policy attached to the specified customer master key (CMK). You
         * cannot perform this operation on a CMK in a different AWS account.</p><p><h3>See
         * Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/GetKeyPolicy">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::GetKeyPolicyOutcomeCallable GetKeyPolicyCallable(const Model::GetKeyPolicyRequest& request) const;

        /**
         * <p>Gets a key policy attached to the specified customer master key (CMK). You
         * cannot perform this operation on a CMK in a different AWS account.</p><p><h3>See
         * Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/GetKeyPolicy">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void GetKeyPolicyAsync(const Model::GetKeyPolicyRequest& request, const GetKeyPolicyResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Gets a Boolean value that indicates whether <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/rotate-keys.html">automatic
         * rotation of the key material</a> is enabled for the specified customer master
         * key (CMK).</p> <p>The result of this operation varies with the key state of the
         * CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p> <ul> <li> <p>Disabled: The key rotation status
         * does not change when you disable a CMK. However, while the CMK is disabled, AWS
         * KMS does not rotate the backing key.</p> </li> <li> <p>Pending deletion: While a
         * CMK is pending deletion, its key rotation status is <code>false</code> and AWS
         * KMS does not rotate the backing key. If you cancel the deletion, the original
         * key rotation status is restored.</p> </li> </ul> <p>To perform this operation on
         * a CMK in a different AWS account, specify the key ARN in the value of the
         * <code>KeyId</code> parameter.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/GetKeyRotationStatus">AWS
         * API Reference</a></p>
         */
        virtual Model::GetKeyRotationStatusOutcome GetKeyRotationStatus(const Model::GetKeyRotationStatusRequest& request) const;

        /**
         * <p>Gets a Boolean value that indicates whether <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/rotate-keys.html">automatic
         * rotation of the key material</a> is enabled for the specified customer master
         * key (CMK).</p> <p>The result of this operation varies with the key state of the
         * CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p> <ul> <li> <p>Disabled: The key rotation status
         * does not change when you disable a CMK. However, while the CMK is disabled, AWS
         * KMS does not rotate the backing key.</p> </li> <li> <p>Pending deletion: While a
         * CMK is pending deletion, its key rotation status is <code>false</code> and AWS
         * KMS does not rotate the backing key. If you cancel the deletion, the original
         * key rotation status is restored.</p> </li> </ul> <p>To perform this operation on
         * a CMK in a different AWS account, specify the key ARN in the value of the
         * <code>KeyId</code> parameter.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/GetKeyRotationStatus">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::GetKeyRotationStatusOutcomeCallable GetKeyRotationStatusCallable(const Model::GetKeyRotationStatusRequest& request) const;

        /**
         * <p>Gets a Boolean value that indicates whether <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/rotate-keys.html">automatic
         * rotation of the key material</a> is enabled for the specified customer master
         * key (CMK).</p> <p>The result of this operation varies with the key state of the
         * CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p> <ul> <li> <p>Disabled: The key rotation status
         * does not change when you disable a CMK. However, while the CMK is disabled, AWS
         * KMS does not rotate the backing key.</p> </li> <li> <p>Pending deletion: While a
         * CMK is pending deletion, its key rotation status is <code>false</code> and AWS
         * KMS does not rotate the backing key. If you cancel the deletion, the original
         * key rotation status is restored.</p> </li> </ul> <p>To perform this operation on
         * a CMK in a different AWS account, specify the key ARN in the value of the
         * <code>KeyId</code> parameter.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/GetKeyRotationStatus">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void GetKeyRotationStatusAsync(const Model::GetKeyRotationStatusRequest& request, const GetKeyRotationStatusResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Returns the items you need in order to import key material into AWS KMS from
         * your existing key management infrastructure. For more information about
         * importing key material into AWS KMS, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/importing-keys.html">Importing
         * Key Material</a> in the <i>AWS Key Management Service Developer Guide</i>.</p>
         * <p>You must specify the key ID of the customer master key (CMK) into which you
         * will import key material. This CMK's <code>Origin</code> must be
         * <code>EXTERNAL</code>. You must also specify the wrapping algorithm and type of
         * wrapping key (public key) that you will use to encrypt the key material. You
         * cannot perform this operation on a CMK in a different AWS account.</p> <p>This
         * operation returns a public key and an import token. Use the public key to
         * encrypt the key material. Store the import token to send with a subsequent
         * <a>ImportKeyMaterial</a> request. The public key and import token from the same
         * response must be used together. These items are valid for 24 hours. When they
         * expire, they cannot be used for a subsequent <a>ImportKeyMaterial</a> request.
         * To get new ones, send another <code>GetParametersForImport</code> request.</p>
         * <p>The result of this operation varies with the key state of the CMK. For
         * details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/GetParametersForImport">AWS
         * API Reference</a></p>
         */
        virtual Model::GetParametersForImportOutcome GetParametersForImport(const Model::GetParametersForImportRequest& request) const;

        /**
         * <p>Returns the items you need in order to import key material into AWS KMS from
         * your existing key management infrastructure. For more information about
         * importing key material into AWS KMS, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/importing-keys.html">Importing
         * Key Material</a> in the <i>AWS Key Management Service Developer Guide</i>.</p>
         * <p>You must specify the key ID of the customer master key (CMK) into which you
         * will import key material. This CMK's <code>Origin</code> must be
         * <code>EXTERNAL</code>. You must also specify the wrapping algorithm and type of
         * wrapping key (public key) that you will use to encrypt the key material. You
         * cannot perform this operation on a CMK in a different AWS account.</p> <p>This
         * operation returns a public key and an import token. Use the public key to
         * encrypt the key material. Store the import token to send with a subsequent
         * <a>ImportKeyMaterial</a> request. The public key and import token from the same
         * response must be used together. These items are valid for 24 hours. When they
         * expire, they cannot be used for a subsequent <a>ImportKeyMaterial</a> request.
         * To get new ones, send another <code>GetParametersForImport</code> request.</p>
         * <p>The result of this operation varies with the key state of the CMK. For
         * details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/GetParametersForImport">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::GetParametersForImportOutcomeCallable GetParametersForImportCallable(const Model::GetParametersForImportRequest& request) const;

        /**
         * <p>Returns the items you need in order to import key material into AWS KMS from
         * your existing key management infrastructure. For more information about
         * importing key material into AWS KMS, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/importing-keys.html">Importing
         * Key Material</a> in the <i>AWS Key Management Service Developer Guide</i>.</p>
         * <p>You must specify the key ID of the customer master key (CMK) into which you
         * will import key material. This CMK's <code>Origin</code> must be
         * <code>EXTERNAL</code>. You must also specify the wrapping algorithm and type of
         * wrapping key (public key) that you will use to encrypt the key material. You
         * cannot perform this operation on a CMK in a different AWS account.</p> <p>This
         * operation returns a public key and an import token. Use the public key to
         * encrypt the key material. Store the import token to send with a subsequent
         * <a>ImportKeyMaterial</a> request. The public key and import token from the same
         * response must be used together. These items are valid for 24 hours. When they
         * expire, they cannot be used for a subsequent <a>ImportKeyMaterial</a> request.
         * To get new ones, send another <code>GetParametersForImport</code> request.</p>
         * <p>The result of this operation varies with the key state of the CMK. For
         * details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/GetParametersForImport">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void GetParametersForImportAsync(const Model::GetParametersForImportRequest& request, const GetParametersForImportResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Imports key material into an existing AWS KMS customer master key (CMK) that
         * was created without key material. You cannot perform this operation on a CMK in
         * a different AWS account. For more information about creating CMKs with no key
         * material and then importing key material, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/importing-keys.html">Importing
         * Key Material</a> in the <i>AWS Key Management Service Developer Guide</i>.</p>
         * <p>Before using this operation, call <a>GetParametersForImport</a>. Its response
         * includes a public key and an import token. Use the public key to encrypt the key
         * material. Then, submit the import token from the same
         * <code>GetParametersForImport</code> response.</p> <p>When calling this
         * operation, you must specify the following values:</p> <ul> <li> <p>The key ID or
         * key ARN of a CMK with no key material. Its <code>Origin</code> must be
         * <code>EXTERNAL</code>.</p> <p>To create a CMK with no key material, call
         * <a>CreateKey</a> and set the value of its <code>Origin</code> parameter to
         * <code>EXTERNAL</code>. To get the <code>Origin</code> of a CMK, call
         * <a>DescribeKey</a>.)</p> </li> <li> <p>The encrypted key material. To get the
         * public key to encrypt the key material, call <a>GetParametersForImport</a>.</p>
         * </li> <li> <p>The import token that <a>GetParametersForImport</a> returned. This
         * token and the public key used to encrypt the key material must have come from
         * the same response.</p> </li> <li> <p>Whether the key material expires and if so,
         * when. If you set an expiration date, you can change it only by reimporting the
         * same key material and specifying a new expiration date. If the key material
         * expires, AWS KMS deletes the key material and the CMK becomes unusable. To use
         * the CMK again, you must reimport the same key material.</p> </li> </ul> <p>When
         * this operation is successful, the key state of the CMK changes from
         * <code>PendingImport</code> to <code>Enabled</code>, and you can use the CMK.
         * After you successfully import key material into a CMK, you can reimport the same
         * key material into that CMK, but you cannot import different key material.</p>
         * <p>The result of this operation varies with the key state of the CMK. For
         * details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ImportKeyMaterial">AWS
         * API Reference</a></p>
         */
        virtual Model::ImportKeyMaterialOutcome ImportKeyMaterial(const Model::ImportKeyMaterialRequest& request) const;

        /**
         * <p>Imports key material into an existing AWS KMS customer master key (CMK) that
         * was created without key material. You cannot perform this operation on a CMK in
         * a different AWS account. For more information about creating CMKs with no key
         * material and then importing key material, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/importing-keys.html">Importing
         * Key Material</a> in the <i>AWS Key Management Service Developer Guide</i>.</p>
         * <p>Before using this operation, call <a>GetParametersForImport</a>. Its response
         * includes a public key and an import token. Use the public key to encrypt the key
         * material. Then, submit the import token from the same
         * <code>GetParametersForImport</code> response.</p> <p>When calling this
         * operation, you must specify the following values:</p> <ul> <li> <p>The key ID or
         * key ARN of a CMK with no key material. Its <code>Origin</code> must be
         * <code>EXTERNAL</code>.</p> <p>To create a CMK with no key material, call
         * <a>CreateKey</a> and set the value of its <code>Origin</code> parameter to
         * <code>EXTERNAL</code>. To get the <code>Origin</code> of a CMK, call
         * <a>DescribeKey</a>.)</p> </li> <li> <p>The encrypted key material. To get the
         * public key to encrypt the key material, call <a>GetParametersForImport</a>.</p>
         * </li> <li> <p>The import token that <a>GetParametersForImport</a> returned. This
         * token and the public key used to encrypt the key material must have come from
         * the same response.</p> </li> <li> <p>Whether the key material expires and if so,
         * when. If you set an expiration date, you can change it only by reimporting the
         * same key material and specifying a new expiration date. If the key material
         * expires, AWS KMS deletes the key material and the CMK becomes unusable. To use
         * the CMK again, you must reimport the same key material.</p> </li> </ul> <p>When
         * this operation is successful, the key state of the CMK changes from
         * <code>PendingImport</code> to <code>Enabled</code>, and you can use the CMK.
         * After you successfully import key material into a CMK, you can reimport the same
         * key material into that CMK, but you cannot import different key material.</p>
         * <p>The result of this operation varies with the key state of the CMK. For
         * details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ImportKeyMaterial">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::ImportKeyMaterialOutcomeCallable ImportKeyMaterialCallable(const Model::ImportKeyMaterialRequest& request) const;

        /**
         * <p>Imports key material into an existing AWS KMS customer master key (CMK) that
         * was created without key material. You cannot perform this operation on a CMK in
         * a different AWS account. For more information about creating CMKs with no key
         * material and then importing key material, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/importing-keys.html">Importing
         * Key Material</a> in the <i>AWS Key Management Service Developer Guide</i>.</p>
         * <p>Before using this operation, call <a>GetParametersForImport</a>. Its response
         * includes a public key and an import token. Use the public key to encrypt the key
         * material. Then, submit the import token from the same
         * <code>GetParametersForImport</code> response.</p> <p>When calling this
         * operation, you must specify the following values:</p> <ul> <li> <p>The key ID or
         * key ARN of a CMK with no key material. Its <code>Origin</code> must be
         * <code>EXTERNAL</code>.</p> <p>To create a CMK with no key material, call
         * <a>CreateKey</a> and set the value of its <code>Origin</code> parameter to
         * <code>EXTERNAL</code>. To get the <code>Origin</code> of a CMK, call
         * <a>DescribeKey</a>.)</p> </li> <li> <p>The encrypted key material. To get the
         * public key to encrypt the key material, call <a>GetParametersForImport</a>.</p>
         * </li> <li> <p>The import token that <a>GetParametersForImport</a> returned. This
         * token and the public key used to encrypt the key material must have come from
         * the same response.</p> </li> <li> <p>Whether the key material expires and if so,
         * when. If you set an expiration date, you can change it only by reimporting the
         * same key material and specifying a new expiration date. If the key material
         * expires, AWS KMS deletes the key material and the CMK becomes unusable. To use
         * the CMK again, you must reimport the same key material.</p> </li> </ul> <p>When
         * this operation is successful, the key state of the CMK changes from
         * <code>PendingImport</code> to <code>Enabled</code>, and you can use the CMK.
         * After you successfully import key material into a CMK, you can reimport the same
         * key material into that CMK, but you cannot import different key material.</p>
         * <p>The result of this operation varies with the key state of the CMK. For
         * details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ImportKeyMaterial">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void ImportKeyMaterialAsync(const Model::ImportKeyMaterialRequest& request, const ImportKeyMaterialResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Gets a list of all aliases in the caller's AWS account and region. You cannot
         * list aliases in other accounts. For more information about aliases, see
         * <a>CreateAlias</a>.</p> <p>By default, the <code>ListAliases</code> command
         * returns all aliases in the account and region. To get only the aliases that
         * point to a particular customer master key (CMK), use the <code>KeyId</code>
         * parameter.</p> <p>The <code>ListAliases</code> response might include several
         * aliases have no <code>TargetKeyId</code> field. These are predefined aliases
         * that AWS has created but has not yet associated with a CMK. Aliases that AWS
         * creates in your account, including predefined aliases, do not count against your
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/limits.html#aliases-limit">AWS
         * KMS aliases limit</a>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ListAliases">AWS API
         * Reference</a></p>
         */
        virtual Model::ListAliasesOutcome ListAliases(const Model::ListAliasesRequest& request) const;

        /**
         * <p>Gets a list of all aliases in the caller's AWS account and region. You cannot
         * list aliases in other accounts. For more information about aliases, see
         * <a>CreateAlias</a>.</p> <p>By default, the <code>ListAliases</code> command
         * returns all aliases in the account and region. To get only the aliases that
         * point to a particular customer master key (CMK), use the <code>KeyId</code>
         * parameter.</p> <p>The <code>ListAliases</code> response might include several
         * aliases have no <code>TargetKeyId</code> field. These are predefined aliases
         * that AWS has created but has not yet associated with a CMK. Aliases that AWS
         * creates in your account, including predefined aliases, do not count against your
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/limits.html#aliases-limit">AWS
         * KMS aliases limit</a>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ListAliases">AWS API
         * Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::ListAliasesOutcomeCallable ListAliasesCallable(const Model::ListAliasesRequest& request) const;

        /**
         * <p>Gets a list of all aliases in the caller's AWS account and region. You cannot
         * list aliases in other accounts. For more information about aliases, see
         * <a>CreateAlias</a>.</p> <p>By default, the <code>ListAliases</code> command
         * returns all aliases in the account and region. To get only the aliases that
         * point to a particular customer master key (CMK), use the <code>KeyId</code>
         * parameter.</p> <p>The <code>ListAliases</code> response might include several
         * aliases have no <code>TargetKeyId</code> field. These are predefined aliases
         * that AWS has created but has not yet associated with a CMK. Aliases that AWS
         * creates in your account, including predefined aliases, do not count against your
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/limits.html#aliases-limit">AWS
         * KMS aliases limit</a>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ListAliases">AWS API
         * Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void ListAliasesAsync(const Model::ListAliasesRequest& request, const ListAliasesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Gets a list of all grants for the specified customer master key (CMK).</p>
         * <p>To perform this operation on a CMK in a different AWS account, specify the
         * key ARN in the value of the <code>KeyId</code> parameter.</p><p><h3>See
         * Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ListGrants">AWS API
         * Reference</a></p>
         */
        virtual Model::ListGrantsOutcome ListGrants(const Model::ListGrantsRequest& request) const;

        /**
         * <p>Gets a list of all grants for the specified customer master key (CMK).</p>
         * <p>To perform this operation on a CMK in a different AWS account, specify the
         * key ARN in the value of the <code>KeyId</code> parameter.</p><p><h3>See
         * Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ListGrants">AWS API
         * Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::ListGrantsOutcomeCallable ListGrantsCallable(const Model::ListGrantsRequest& request) const;

        /**
         * <p>Gets a list of all grants for the specified customer master key (CMK).</p>
         * <p>To perform this operation on a CMK in a different AWS account, specify the
         * key ARN in the value of the <code>KeyId</code> parameter.</p><p><h3>See
         * Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ListGrants">AWS API
         * Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void ListGrantsAsync(const Model::ListGrantsRequest& request, const ListGrantsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Gets the names of the key policies that are attached to a customer master key
         * (CMK). This operation is designed to get policy names that you can use in a
         * <a>GetKeyPolicy</a> operation. However, the only valid policy name is
         * <code>default</code>. You cannot perform this operation on a CMK in a different
         * AWS account.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ListKeyPolicies">AWS
         * API Reference</a></p>
         */
        virtual Model::ListKeyPoliciesOutcome ListKeyPolicies(const Model::ListKeyPoliciesRequest& request) const;

        /**
         * <p>Gets the names of the key policies that are attached to a customer master key
         * (CMK). This operation is designed to get policy names that you can use in a
         * <a>GetKeyPolicy</a> operation. However, the only valid policy name is
         * <code>default</code>. You cannot perform this operation on a CMK in a different
         * AWS account.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ListKeyPolicies">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::ListKeyPoliciesOutcomeCallable ListKeyPoliciesCallable(const Model::ListKeyPoliciesRequest& request) const;

        /**
         * <p>Gets the names of the key policies that are attached to a customer master key
         * (CMK). This operation is designed to get policy names that you can use in a
         * <a>GetKeyPolicy</a> operation. However, the only valid policy name is
         * <code>default</code>. You cannot perform this operation on a CMK in a different
         * AWS account.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ListKeyPolicies">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void ListKeyPoliciesAsync(const Model::ListKeyPoliciesRequest& request, const ListKeyPoliciesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Gets a list of all customer master keys (CMKs) in the caller's AWS account
         * and region.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ListKeys">AWS API
         * Reference</a></p>
         */
        virtual Model::ListKeysOutcome ListKeys(const Model::ListKeysRequest& request) const;

        /**
         * <p>Gets a list of all customer master keys (CMKs) in the caller's AWS account
         * and region.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ListKeys">AWS API
         * Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::ListKeysOutcomeCallable ListKeysCallable(const Model::ListKeysRequest& request) const;

        /**
         * <p>Gets a list of all customer master keys (CMKs) in the caller's AWS account
         * and region.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ListKeys">AWS API
         * Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void ListKeysAsync(const Model::ListKeysRequest& request, const ListKeysResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Returns a list of all tags for the specified customer master key (CMK).</p>
         * <p>You cannot perform this operation on a CMK in a different AWS
         * account.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ListResourceTags">AWS
         * API Reference</a></p>
         */
        virtual Model::ListResourceTagsOutcome ListResourceTags(const Model::ListResourceTagsRequest& request) const;

        /**
         * <p>Returns a list of all tags for the specified customer master key (CMK).</p>
         * <p>You cannot perform this operation on a CMK in a different AWS
         * account.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ListResourceTags">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::ListResourceTagsOutcomeCallable ListResourceTagsCallable(const Model::ListResourceTagsRequest& request) const;

        /**
         * <p>Returns a list of all tags for the specified customer master key (CMK).</p>
         * <p>You cannot perform this operation on a CMK in a different AWS
         * account.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ListResourceTags">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void ListResourceTagsAsync(const Model::ListResourceTagsRequest& request, const ListResourceTagsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Returns a list of all grants for which the grant's
         * <code>RetiringPrincipal</code> matches the one specified.</p> <p>A typical use
         * is to list all grants that you are able to retire. To retire a grant, use
         * <a>RetireGrant</a>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ListRetirableGrants">AWS
         * API Reference</a></p>
         */
        virtual Model::ListRetirableGrantsOutcome ListRetirableGrants(const Model::ListRetirableGrantsRequest& request) const;

        /**
         * <p>Returns a list of all grants for which the grant's
         * <code>RetiringPrincipal</code> matches the one specified.</p> <p>A typical use
         * is to list all grants that you are able to retire. To retire a grant, use
         * <a>RetireGrant</a>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ListRetirableGrants">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::ListRetirableGrantsOutcomeCallable ListRetirableGrantsCallable(const Model::ListRetirableGrantsRequest& request) const;

        /**
         * <p>Returns a list of all grants for which the grant's
         * <code>RetiringPrincipal</code> matches the one specified.</p> <p>A typical use
         * is to list all grants that you are able to retire. To retire a grant, use
         * <a>RetireGrant</a>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ListRetirableGrants">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void ListRetirableGrantsAsync(const Model::ListRetirableGrantsRequest& request, const ListRetirableGrantsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Attaches a key policy to the specified customer master key (CMK). You cannot
         * perform this operation on a CMK in a different AWS account.</p> <p>For more
         * information about key policies, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-policies.html">Key
         * Policies</a> in the <i>AWS Key Management Service Developer
         * Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/PutKeyPolicy">AWS
         * API Reference</a></p>
         */
        virtual Model::PutKeyPolicyOutcome PutKeyPolicy(const Model::PutKeyPolicyRequest& request) const;

        /**
         * <p>Attaches a key policy to the specified customer master key (CMK). You cannot
         * perform this operation on a CMK in a different AWS account.</p> <p>For more
         * information about key policies, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-policies.html">Key
         * Policies</a> in the <i>AWS Key Management Service Developer
         * Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/PutKeyPolicy">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::PutKeyPolicyOutcomeCallable PutKeyPolicyCallable(const Model::PutKeyPolicyRequest& request) const;

        /**
         * <p>Attaches a key policy to the specified customer master key (CMK). You cannot
         * perform this operation on a CMK in a different AWS account.</p> <p>For more
         * information about key policies, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-policies.html">Key
         * Policies</a> in the <i>AWS Key Management Service Developer
         * Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/PutKeyPolicy">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void PutKeyPolicyAsync(const Model::PutKeyPolicyRequest& request, const PutKeyPolicyResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Encrypts data on the server side with a new customer master key (CMK) without
         * exposing the plaintext of the data on the client side. The data is first
         * decrypted and then reencrypted. You can also use this operation to change the
         * encryption context of a ciphertext. </p> <p>You can reencrypt data using CMKs in
         * different AWS accounts.</p> <p>Unlike other operations, <code>ReEncrypt</code>
         * is authorized twice, once as <code>ReEncryptFrom</code> on the source CMK and
         * once as <code>ReEncryptTo</code> on the destination CMK. We recommend that you
         * include the <code>"kms:ReEncrypt*"</code> permission in your <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-policies.html">key
         * policies</a> to permit reencryption from or to the CMK. This permission is
         * automatically included in the key policy when you create a CMK through the
         * console, but you must include it manually when you create a CMK programmatically
         * or when you set a key policy with the <a>PutKeyPolicy</a> operation.</p> <p>The
         * result of this operation varies with the key state of the CMK. For details, see
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ReEncrypt">AWS API
         * Reference</a></p>
         */
        virtual Model::ReEncryptOutcome ReEncrypt(const Model::ReEncryptRequest& request) const;

        /**
         * <p>Encrypts data on the server side with a new customer master key (CMK) without
         * exposing the plaintext of the data on the client side. The data is first
         * decrypted and then reencrypted. You can also use this operation to change the
         * encryption context of a ciphertext. </p> <p>You can reencrypt data using CMKs in
         * different AWS accounts.</p> <p>Unlike other operations, <code>ReEncrypt</code>
         * is authorized twice, once as <code>ReEncryptFrom</code> on the source CMK and
         * once as <code>ReEncryptTo</code> on the destination CMK. We recommend that you
         * include the <code>"kms:ReEncrypt*"</code> permission in your <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-policies.html">key
         * policies</a> to permit reencryption from or to the CMK. This permission is
         * automatically included in the key policy when you create a CMK through the
         * console, but you must include it manually when you create a CMK programmatically
         * or when you set a key policy with the <a>PutKeyPolicy</a> operation.</p> <p>The
         * result of this operation varies with the key state of the CMK. For details, see
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ReEncrypt">AWS API
         * Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::ReEncryptOutcomeCallable ReEncryptCallable(const Model::ReEncryptRequest& request) const;

        /**
         * <p>Encrypts data on the server side with a new customer master key (CMK) without
         * exposing the plaintext of the data on the client side. The data is first
         * decrypted and then reencrypted. You can also use this operation to change the
         * encryption context of a ciphertext. </p> <p>You can reencrypt data using CMKs in
         * different AWS accounts.</p> <p>Unlike other operations, <code>ReEncrypt</code>
         * is authorized twice, once as <code>ReEncryptFrom</code> on the source CMK and
         * once as <code>ReEncryptTo</code> on the destination CMK. We recommend that you
         * include the <code>"kms:ReEncrypt*"</code> permission in your <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-policies.html">key
         * policies</a> to permit reencryption from or to the CMK. This permission is
         * automatically included in the key policy when you create a CMK through the
         * console, but you must include it manually when you create a CMK programmatically
         * or when you set a key policy with the <a>PutKeyPolicy</a> operation.</p> <p>The
         * result of this operation varies with the key state of the CMK. For details, see
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ReEncrypt">AWS API
         * Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void ReEncryptAsync(const Model::ReEncryptRequest& request, const ReEncryptResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Retires a grant. To clean up, you can retire a grant when you're done using
         * it. You should revoke a grant when you intend to actively deny operations that
         * depend on it. The following are permitted to call this API:</p> <ul> <li> <p>The
         * AWS account (root user) under which the grant was created</p> </li> <li> <p>The
         * <code>RetiringPrincipal</code>, if present in the grant</p> </li> <li> <p>The
         * <code>GranteePrincipal</code>, if <code>RetireGrant</code> is an operation
         * specified in the grant</p> </li> </ul> <p>You must identify the grant to retire
         * by its grant token or by a combination of the grant ID and the Amazon Resource
         * Name (ARN) of the customer master key (CMK). A grant token is a unique
         * variable-length base64-encoded string. A grant ID is a 64 character unique
         * identifier of a grant. The <a>CreateGrant</a> operation returns
         * both.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/RetireGrant">AWS API
         * Reference</a></p>
         */
        virtual Model::RetireGrantOutcome RetireGrant(const Model::RetireGrantRequest& request) const;

        /**
         * <p>Retires a grant. To clean up, you can retire a grant when you're done using
         * it. You should revoke a grant when you intend to actively deny operations that
         * depend on it. The following are permitted to call this API:</p> <ul> <li> <p>The
         * AWS account (root user) under which the grant was created</p> </li> <li> <p>The
         * <code>RetiringPrincipal</code>, if present in the grant</p> </li> <li> <p>The
         * <code>GranteePrincipal</code>, if <code>RetireGrant</code> is an operation
         * specified in the grant</p> </li> </ul> <p>You must identify the grant to retire
         * by its grant token or by a combination of the grant ID and the Amazon Resource
         * Name (ARN) of the customer master key (CMK). A grant token is a unique
         * variable-length base64-encoded string. A grant ID is a 64 character unique
         * identifier of a grant. The <a>CreateGrant</a> operation returns
         * both.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/RetireGrant">AWS API
         * Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::RetireGrantOutcomeCallable RetireGrantCallable(const Model::RetireGrantRequest& request) const;

        /**
         * <p>Retires a grant. To clean up, you can retire a grant when you're done using
         * it. You should revoke a grant when you intend to actively deny operations that
         * depend on it. The following are permitted to call this API:</p> <ul> <li> <p>The
         * AWS account (root user) under which the grant was created</p> </li> <li> <p>The
         * <code>RetiringPrincipal</code>, if present in the grant</p> </li> <li> <p>The
         * <code>GranteePrincipal</code>, if <code>RetireGrant</code> is an operation
         * specified in the grant</p> </li> </ul> <p>You must identify the grant to retire
         * by its grant token or by a combination of the grant ID and the Amazon Resource
         * Name (ARN) of the customer master key (CMK). A grant token is a unique
         * variable-length base64-encoded string. A grant ID is a 64 character unique
         * identifier of a grant. The <a>CreateGrant</a> operation returns
         * both.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/RetireGrant">AWS API
         * Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void RetireGrantAsync(const Model::RetireGrantRequest& request, const RetireGrantResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Revokes the specified grant for the specified customer master key (CMK). You
         * can revoke a grant to actively deny operations that depend on it.</p> <p>To
         * perform this operation on a CMK in a different AWS account, specify the key ARN
         * in the value of the <code>KeyId</code> parameter.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/RevokeGrant">AWS API
         * Reference</a></p>
         */
        virtual Model::RevokeGrantOutcome RevokeGrant(const Model::RevokeGrantRequest& request) const;

        /**
         * <p>Revokes the specified grant for the specified customer master key (CMK). You
         * can revoke a grant to actively deny operations that depend on it.</p> <p>To
         * perform this operation on a CMK in a different AWS account, specify the key ARN
         * in the value of the <code>KeyId</code> parameter.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/RevokeGrant">AWS API
         * Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::RevokeGrantOutcomeCallable RevokeGrantCallable(const Model::RevokeGrantRequest& request) const;

        /**
         * <p>Revokes the specified grant for the specified customer master key (CMK). You
         * can revoke a grant to actively deny operations that depend on it.</p> <p>To
         * perform this operation on a CMK in a different AWS account, specify the key ARN
         * in the value of the <code>KeyId</code> parameter.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/RevokeGrant">AWS API
         * Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void RevokeGrantAsync(const Model::RevokeGrantRequest& request, const RevokeGrantResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Schedules the deletion of a customer master key (CMK). You may provide a
         * waiting period, specified in days, before deletion occurs. If you do not provide
         * a waiting period, the default period of 30 days is used. When this operation is
         * successful, the key state of the CMK changes to <code>PendingDeletion</code>.
         * Before the waiting period ends, you can use <a>CancelKeyDeletion</a> to cancel
         * the deletion of the CMK. After the waiting period ends, AWS KMS deletes the CMK
         * and all AWS KMS data associated with it, including all aliases that refer to
         * it.</p> <important> <p>Deleting a CMK is a destructive and potentially dangerous
         * operation. When a CMK is deleted, all data that was encrypted under the CMK is
         * unrecoverable. To prevent the use of a CMK without deleting it, use
         * <a>DisableKey</a>.</p> </important> <p>If you schedule deletion of a CMK from a
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a>, when the waiting period expires, <code>ScheduleKeyDeletion</code>
         * deletes the CMK from AWS KMS. Then AWS KMS makes a best effort to delete the key
         * material from the associated AWS CloudHSM cluster. However, you might need to
         * manually <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/fix-keystore.html#fix-keystore-orphaned-key">delete
         * the orphaned key material</a> from the cluster and its backups.</p> <p>You
         * cannot perform this operation on a CMK in a different AWS account.</p> <p>For
         * more information about scheduling a CMK for deletion, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/deleting-keys.html">Deleting
         * Customer Master Keys</a> in the <i>AWS Key Management Service Developer
         * Guide</i>.</p> <p>The result of this operation varies with the key state of the
         * CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ScheduleKeyDeletion">AWS
         * API Reference</a></p>
         */
        virtual Model::ScheduleKeyDeletionOutcome ScheduleKeyDeletion(const Model::ScheduleKeyDeletionRequest& request) const;

        /**
         * <p>Schedules the deletion of a customer master key (CMK). You may provide a
         * waiting period, specified in days, before deletion occurs. If you do not provide
         * a waiting period, the default period of 30 days is used. When this operation is
         * successful, the key state of the CMK changes to <code>PendingDeletion</code>.
         * Before the waiting period ends, you can use <a>CancelKeyDeletion</a> to cancel
         * the deletion of the CMK. After the waiting period ends, AWS KMS deletes the CMK
         * and all AWS KMS data associated with it, including all aliases that refer to
         * it.</p> <important> <p>Deleting a CMK is a destructive and potentially dangerous
         * operation. When a CMK is deleted, all data that was encrypted under the CMK is
         * unrecoverable. To prevent the use of a CMK without deleting it, use
         * <a>DisableKey</a>.</p> </important> <p>If you schedule deletion of a CMK from a
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a>, when the waiting period expires, <code>ScheduleKeyDeletion</code>
         * deletes the CMK from AWS KMS. Then AWS KMS makes a best effort to delete the key
         * material from the associated AWS CloudHSM cluster. However, you might need to
         * manually <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/fix-keystore.html#fix-keystore-orphaned-key">delete
         * the orphaned key material</a> from the cluster and its backups.</p> <p>You
         * cannot perform this operation on a CMK in a different AWS account.</p> <p>For
         * more information about scheduling a CMK for deletion, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/deleting-keys.html">Deleting
         * Customer Master Keys</a> in the <i>AWS Key Management Service Developer
         * Guide</i>.</p> <p>The result of this operation varies with the key state of the
         * CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ScheduleKeyDeletion">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::ScheduleKeyDeletionOutcomeCallable ScheduleKeyDeletionCallable(const Model::ScheduleKeyDeletionRequest& request) const;

        /**
         * <p>Schedules the deletion of a customer master key (CMK). You may provide a
         * waiting period, specified in days, before deletion occurs. If you do not provide
         * a waiting period, the default period of 30 days is used. When this operation is
         * successful, the key state of the CMK changes to <code>PendingDeletion</code>.
         * Before the waiting period ends, you can use <a>CancelKeyDeletion</a> to cancel
         * the deletion of the CMK. After the waiting period ends, AWS KMS deletes the CMK
         * and all AWS KMS data associated with it, including all aliases that refer to
         * it.</p> <important> <p>Deleting a CMK is a destructive and potentially dangerous
         * operation. When a CMK is deleted, all data that was encrypted under the CMK is
         * unrecoverable. To prevent the use of a CMK without deleting it, use
         * <a>DisableKey</a>.</p> </important> <p>If you schedule deletion of a CMK from a
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-overview.html">custom
         * key store</a>, when the waiting period expires, <code>ScheduleKeyDeletion</code>
         * deletes the CMK from AWS KMS. Then AWS KMS makes a best effort to delete the key
         * material from the associated AWS CloudHSM cluster. However, you might need to
         * manually <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/fix-keystore.html#fix-keystore-orphaned-key">delete
         * the orphaned key material</a> from the cluster and its backups.</p> <p>You
         * cannot perform this operation on a CMK in a different AWS account.</p> <p>For
         * more information about scheduling a CMK for deletion, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/deleting-keys.html">Deleting
         * Customer Master Keys</a> in the <i>AWS Key Management Service Developer
         * Guide</i>.</p> <p>The result of this operation varies with the key state of the
         * CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/ScheduleKeyDeletion">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void ScheduleKeyDeletionAsync(const Model::ScheduleKeyDeletionRequest& request, const ScheduleKeyDeletionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Adds or edits tags for a customer master key (CMK). You cannot perform this
         * operation on a CMK in a different AWS account.</p> <p>Each tag consists of a tag
         * key and a tag value. Tag keys and tag values are both required, but tag values
         * can be empty (null) strings.</p> <p>You can only use a tag key once for each
         * CMK. If you use the tag key again, AWS KMS replaces the current tag value with
         * the specified value.</p> <p>For information about the rules that apply to tag
         * keys and tag values, see <a
         * href="http://docs.aws.amazon.com/awsaccountbilling/latest/aboutv2/allocation-tag-restrictions.html">User-Defined
         * Tag Restrictions</a> in the <i>AWS Billing and Cost Management User
         * Guide</i>.</p> <p>The result of this operation varies with the key state of the
         * CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/TagResource">AWS API
         * Reference</a></p>
         */
        virtual Model::TagResourceOutcome TagResource(const Model::TagResourceRequest& request) const;

        /**
         * <p>Adds or edits tags for a customer master key (CMK). You cannot perform this
         * operation on a CMK in a different AWS account.</p> <p>Each tag consists of a tag
         * key and a tag value. Tag keys and tag values are both required, but tag values
         * can be empty (null) strings.</p> <p>You can only use a tag key once for each
         * CMK. If you use the tag key again, AWS KMS replaces the current tag value with
         * the specified value.</p> <p>For information about the rules that apply to tag
         * keys and tag values, see <a
         * href="http://docs.aws.amazon.com/awsaccountbilling/latest/aboutv2/allocation-tag-restrictions.html">User-Defined
         * Tag Restrictions</a> in the <i>AWS Billing and Cost Management User
         * Guide</i>.</p> <p>The result of this operation varies with the key state of the
         * CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/TagResource">AWS API
         * Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::TagResourceOutcomeCallable TagResourceCallable(const Model::TagResourceRequest& request) const;

        /**
         * <p>Adds or edits tags for a customer master key (CMK). You cannot perform this
         * operation on a CMK in a different AWS account.</p> <p>Each tag consists of a tag
         * key and a tag value. Tag keys and tag values are both required, but tag values
         * can be empty (null) strings.</p> <p>You can only use a tag key once for each
         * CMK. If you use the tag key again, AWS KMS replaces the current tag value with
         * the specified value.</p> <p>For information about the rules that apply to tag
         * keys and tag values, see <a
         * href="http://docs.aws.amazon.com/awsaccountbilling/latest/aboutv2/allocation-tag-restrictions.html">User-Defined
         * Tag Restrictions</a> in the <i>AWS Billing and Cost Management User
         * Guide</i>.</p> <p>The result of this operation varies with the key state of the
         * CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/TagResource">AWS API
         * Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void TagResourceAsync(const Model::TagResourceRequest& request, const TagResourceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Removes the specified tags from the specified customer master key (CMK). You
         * cannot perform this operation on a CMK in a different AWS account.</p> <p>To
         * remove a tag, specify the tag key. To change the tag value of an existing tag
         * key, use <a>TagResource</a>.</p> <p>The result of this operation varies with the
         * key state of the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/UntagResource">AWS
         * API Reference</a></p>
         */
        virtual Model::UntagResourceOutcome UntagResource(const Model::UntagResourceRequest& request) const;

        /**
         * <p>Removes the specified tags from the specified customer master key (CMK). You
         * cannot perform this operation on a CMK in a different AWS account.</p> <p>To
         * remove a tag, specify the tag key. To change the tag value of an existing tag
         * key, use <a>TagResource</a>.</p> <p>The result of this operation varies with the
         * key state of the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/UntagResource">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::UntagResourceOutcomeCallable UntagResourceCallable(const Model::UntagResourceRequest& request) const;

        /**
         * <p>Removes the specified tags from the specified customer master key (CMK). You
         * cannot perform this operation on a CMK in a different AWS account.</p> <p>To
         * remove a tag, specify the tag key. To change the tag value of an existing tag
         * key, use <a>TagResource</a>.</p> <p>The result of this operation varies with the
         * key state of the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/UntagResource">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void UntagResourceAsync(const Model::UntagResourceRequest& request, const UntagResourceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Associates an existing alias with a different customer master key (CMK). Each
         * CMK can have multiple aliases, but the aliases must be unique within the account
         * and region. You cannot perform this operation on an alias in a different AWS
         * account.</p> <p>This operation works only on existing aliases. To change the
         * alias of a CMK to a new value, use <a>CreateAlias</a> to create a new alias and
         * <a>DeleteAlias</a> to delete the old alias.</p> <p>Because an alias is not a
         * property of a CMK, you can create, update, and delete the aliases of a CMK
         * without affecting the CMK. Also, aliases do not appear in the response from the
         * <a>DescribeKey</a> operation. To get the aliases of all CMKs in the account, use
         * the <a>ListAliases</a> operation. </p> <p>An alias name can contain only
         * alphanumeric characters, forward slashes (/), underscores (_), and dashes (-).
         * An alias must start with the word <code>alias</code> followed by a forward slash
         * (<code>alias/</code>). The alias name can contain only alphanumeric characters,
         * forward slashes (/), underscores (_), and dashes (-). Alias names cannot begin
         * with <code>aws</code>; that alias name prefix is reserved by Amazon Web Services
         * (AWS).</p> <p>The result of this operation varies with the key state of the CMK.
         * For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/UpdateAlias">AWS API
         * Reference</a></p>
         */
        virtual Model::UpdateAliasOutcome UpdateAlias(const Model::UpdateAliasRequest& request) const;

        /**
         * <p>Associates an existing alias with a different customer master key (CMK). Each
         * CMK can have multiple aliases, but the aliases must be unique within the account
         * and region. You cannot perform this operation on an alias in a different AWS
         * account.</p> <p>This operation works only on existing aliases. To change the
         * alias of a CMK to a new value, use <a>CreateAlias</a> to create a new alias and
         * <a>DeleteAlias</a> to delete the old alias.</p> <p>Because an alias is not a
         * property of a CMK, you can create, update, and delete the aliases of a CMK
         * without affecting the CMK. Also, aliases do not appear in the response from the
         * <a>DescribeKey</a> operation. To get the aliases of all CMKs in the account, use
         * the <a>ListAliases</a> operation. </p> <p>An alias name can contain only
         * alphanumeric characters, forward slashes (/), underscores (_), and dashes (-).
         * An alias must start with the word <code>alias</code> followed by a forward slash
         * (<code>alias/</code>). The alias name can contain only alphanumeric characters,
         * forward slashes (/), underscores (_), and dashes (-). Alias names cannot begin
         * with <code>aws</code>; that alias name prefix is reserved by Amazon Web Services
         * (AWS).</p> <p>The result of this operation varies with the key state of the CMK.
         * For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/UpdateAlias">AWS API
         * Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::UpdateAliasOutcomeCallable UpdateAliasCallable(const Model::UpdateAliasRequest& request) const;

        /**
         * <p>Associates an existing alias with a different customer master key (CMK). Each
         * CMK can have multiple aliases, but the aliases must be unique within the account
         * and region. You cannot perform this operation on an alias in a different AWS
         * account.</p> <p>This operation works only on existing aliases. To change the
         * alias of a CMK to a new value, use <a>CreateAlias</a> to create a new alias and
         * <a>DeleteAlias</a> to delete the old alias.</p> <p>Because an alias is not a
         * property of a CMK, you can create, update, and delete the aliases of a CMK
         * without affecting the CMK. Also, aliases do not appear in the response from the
         * <a>DescribeKey</a> operation. To get the aliases of all CMKs in the account, use
         * the <a>ListAliases</a> operation. </p> <p>An alias name can contain only
         * alphanumeric characters, forward slashes (/), underscores (_), and dashes (-).
         * An alias must start with the word <code>alias</code> followed by a forward slash
         * (<code>alias/</code>). The alias name can contain only alphanumeric characters,
         * forward slashes (/), underscores (_), and dashes (-). Alias names cannot begin
         * with <code>aws</code>; that alias name prefix is reserved by Amazon Web Services
         * (AWS).</p> <p>The result of this operation varies with the key state of the CMK.
         * For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/UpdateAlias">AWS API
         * Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void UpdateAliasAsync(const Model::UpdateAliasRequest& request, const UpdateAliasResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Changes the properties of a custom key store. Use the
         * <code>CustomKeyStoreId</code> parameter to identify the custom key store you
         * want to edit. Use the remaining parameters to change the properties of the
         * custom key store.</p> <p>You can only update a custom key store that is
         * disconnected. To disconnect the custom key store, use
         * <a>DisconnectCustomKeyStore</a>. To reconnect the custom key store after the
         * update completes, use <a>ConnectCustomKeyStore</a>. To find the connection state
         * of a custom key store, use the <a>DescribeCustomKeyStores</a> operation.</p>
         * <p>Use the <code>NewCustomKeyStoreName</code> parameter to change the friendly
         * name of the custom key store to the value that you specify.</p> <p>Use the
         * <code>KeyStorePassword</code> parameter tell AWS KMS the current password of the
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-concepts.html#concept-kmsuser">
         * <code>kmsuser</code> crypto user (CU)</a> in the associated AWS CloudHSM
         * cluster. You can use this parameter to fix connection failures that occur when
         * AWS KMS cannot log into the associated cluster because the <code>kmsuser</code>
         * password has changed. This value does not change the password in the AWS
         * CloudHSM cluster.</p> <p>Use the <code>CloudHsmClusterId</code> parameter to
         * associate the custom key store with a related AWS CloudHSM cluster, that is, a
         * cluster that shares a backup history with the original cluster. You can use this
         * parameter to repair a custom key store if its AWS CloudHSM cluster becomes
         * corrupted or is deleted, or when you need to create or restore a cluster from a
         * backup.</p> <p>The cluster ID must identify a AWS CloudHSM cluster with the
         * following requirements.</p> <ul> <li> <p>The cluster must be active and be in
         * the same AWS account and Region as the custom key store.</p> </li> <li> <p>The
         * cluster must have the same cluster certificate as the original cluster. You
         * cannot use this parameter to associate the custom key store with an unrelated
         * cluster. To view the cluster certificate, use the AWS CloudHSM <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/APIReference/API_DescribeClusters.html">DescribeClusters</a>
         * operation. Clusters that share a backup history have the same cluster
         * certificate.</p> </li> <li> <p>The cluster must be configured with subnets in at
         * least two different Availability Zones in the Region. Because AWS CloudHSM is
         * not supported in all Availability Zones, we recommend that the cluster have
         * subnets in all Availability Zones in the Region.</p> </li> <li> <p>The cluster
         * must contain at least two active HSMs, each in a different Availability
         * Zone.</p> </li> </ul> <p>If the operation succeeds, it returns a JSON object
         * with no properties.</p> <p>This operation is part of the <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/custom-key-store-overview.html">Custom
         * Key Store feature</a> feature in AWS KMS, which combines the convenience and
         * extensive integration of AWS KMS with the isolation and control of a
         * single-tenant key store.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/UpdateCustomKeyStore">AWS
         * API Reference</a></p>
         */
        virtual Model::UpdateCustomKeyStoreOutcome UpdateCustomKeyStore(const Model::UpdateCustomKeyStoreRequest& request) const;

        /**
         * <p>Changes the properties of a custom key store. Use the
         * <code>CustomKeyStoreId</code> parameter to identify the custom key store you
         * want to edit. Use the remaining parameters to change the properties of the
         * custom key store.</p> <p>You can only update a custom key store that is
         * disconnected. To disconnect the custom key store, use
         * <a>DisconnectCustomKeyStore</a>. To reconnect the custom key store after the
         * update completes, use <a>ConnectCustomKeyStore</a>. To find the connection state
         * of a custom key store, use the <a>DescribeCustomKeyStores</a> operation.</p>
         * <p>Use the <code>NewCustomKeyStoreName</code> parameter to change the friendly
         * name of the custom key store to the value that you specify.</p> <p>Use the
         * <code>KeyStorePassword</code> parameter tell AWS KMS the current password of the
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-concepts.html#concept-kmsuser">
         * <code>kmsuser</code> crypto user (CU)</a> in the associated AWS CloudHSM
         * cluster. You can use this parameter to fix connection failures that occur when
         * AWS KMS cannot log into the associated cluster because the <code>kmsuser</code>
         * password has changed. This value does not change the password in the AWS
         * CloudHSM cluster.</p> <p>Use the <code>CloudHsmClusterId</code> parameter to
         * associate the custom key store with a related AWS CloudHSM cluster, that is, a
         * cluster that shares a backup history with the original cluster. You can use this
         * parameter to repair a custom key store if its AWS CloudHSM cluster becomes
         * corrupted or is deleted, or when you need to create or restore a cluster from a
         * backup.</p> <p>The cluster ID must identify a AWS CloudHSM cluster with the
         * following requirements.</p> <ul> <li> <p>The cluster must be active and be in
         * the same AWS account and Region as the custom key store.</p> </li> <li> <p>The
         * cluster must have the same cluster certificate as the original cluster. You
         * cannot use this parameter to associate the custom key store with an unrelated
         * cluster. To view the cluster certificate, use the AWS CloudHSM <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/APIReference/API_DescribeClusters.html">DescribeClusters</a>
         * operation. Clusters that share a backup history have the same cluster
         * certificate.</p> </li> <li> <p>The cluster must be configured with subnets in at
         * least two different Availability Zones in the Region. Because AWS CloudHSM is
         * not supported in all Availability Zones, we recommend that the cluster have
         * subnets in all Availability Zones in the Region.</p> </li> <li> <p>The cluster
         * must contain at least two active HSMs, each in a different Availability
         * Zone.</p> </li> </ul> <p>If the operation succeeds, it returns a JSON object
         * with no properties.</p> <p>This operation is part of the <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/custom-key-store-overview.html">Custom
         * Key Store feature</a> feature in AWS KMS, which combines the convenience and
         * extensive integration of AWS KMS with the isolation and control of a
         * single-tenant key store.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/UpdateCustomKeyStore">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::UpdateCustomKeyStoreOutcomeCallable UpdateCustomKeyStoreCallable(const Model::UpdateCustomKeyStoreRequest& request) const;

        /**
         * <p>Changes the properties of a custom key store. Use the
         * <code>CustomKeyStoreId</code> parameter to identify the custom key store you
         * want to edit. Use the remaining parameters to change the properties of the
         * custom key store.</p> <p>You can only update a custom key store that is
         * disconnected. To disconnect the custom key store, use
         * <a>DisconnectCustomKeyStore</a>. To reconnect the custom key store after the
         * update completes, use <a>ConnectCustomKeyStore</a>. To find the connection state
         * of a custom key store, use the <a>DescribeCustomKeyStores</a> operation.</p>
         * <p>Use the <code>NewCustomKeyStoreName</code> parameter to change the friendly
         * name of the custom key store to the value that you specify.</p> <p>Use the
         * <code>KeyStorePassword</code> parameter tell AWS KMS the current password of the
         * <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-store-concepts.html#concept-kmsuser">
         * <code>kmsuser</code> crypto user (CU)</a> in the associated AWS CloudHSM
         * cluster. You can use this parameter to fix connection failures that occur when
         * AWS KMS cannot log into the associated cluster because the <code>kmsuser</code>
         * password has changed. This value does not change the password in the AWS
         * CloudHSM cluster.</p> <p>Use the <code>CloudHsmClusterId</code> parameter to
         * associate the custom key store with a related AWS CloudHSM cluster, that is, a
         * cluster that shares a backup history with the original cluster. You can use this
         * parameter to repair a custom key store if its AWS CloudHSM cluster becomes
         * corrupted or is deleted, or when you need to create or restore a cluster from a
         * backup.</p> <p>The cluster ID must identify a AWS CloudHSM cluster with the
         * following requirements.</p> <ul> <li> <p>The cluster must be active and be in
         * the same AWS account and Region as the custom key store.</p> </li> <li> <p>The
         * cluster must have the same cluster certificate as the original cluster. You
         * cannot use this parameter to associate the custom key store with an unrelated
         * cluster. To view the cluster certificate, use the AWS CloudHSM <a
         * href="http://docs.aws.amazon.com/cloudhsm/latest/APIReference/API_DescribeClusters.html">DescribeClusters</a>
         * operation. Clusters that share a backup history have the same cluster
         * certificate.</p> </li> <li> <p>The cluster must be configured with subnets in at
         * least two different Availability Zones in the Region. Because AWS CloudHSM is
         * not supported in all Availability Zones, we recommend that the cluster have
         * subnets in all Availability Zones in the Region.</p> </li> <li> <p>The cluster
         * must contain at least two active HSMs, each in a different Availability
         * Zone.</p> </li> </ul> <p>If the operation succeeds, it returns a JSON object
         * with no properties.</p> <p>This operation is part of the <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/custom-key-store-overview.html">Custom
         * Key Store feature</a> feature in AWS KMS, which combines the convenience and
         * extensive integration of AWS KMS with the isolation and control of a
         * single-tenant key store.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/UpdateCustomKeyStore">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void UpdateCustomKeyStoreAsync(const Model::UpdateCustomKeyStoreRequest& request, const UpdateCustomKeyStoreResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

        /**
         * <p>Updates the description of a customer master key (CMK). To see the decription
         * of a CMK, use <a>DescribeKey</a>. </p> <p>You cannot perform this operation on a
         * CMK in a different AWS account.</p> <p>The result of this operation varies with
         * the key state of the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/UpdateKeyDescription">AWS
         * API Reference</a></p>
         */
        virtual Model::UpdateKeyDescriptionOutcome UpdateKeyDescription(const Model::UpdateKeyDescriptionRequest& request) const;

        /**
         * <p>Updates the description of a customer master key (CMK). To see the decription
         * of a CMK, use <a>DescribeKey</a>. </p> <p>You cannot perform this operation on a
         * CMK in a different AWS account.</p> <p>The result of this operation varies with
         * the key state of the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/UpdateKeyDescription">AWS
         * API Reference</a></p>
         *
         * returns a future to the operation so that it can be executed in parallel to other requests.
         */
        virtual Model::UpdateKeyDescriptionOutcomeCallable UpdateKeyDescriptionCallable(const Model::UpdateKeyDescriptionRequest& request) const;

        /**
         * <p>Updates the description of a customer master key (CMK). To see the decription
         * of a CMK, use <a>DescribeKey</a>. </p> <p>You cannot perform this operation on a
         * CMK in a different AWS account.</p> <p>The result of this operation varies with
         * the key state of the CMK. For details, see <a
         * href="http://docs.aws.amazon.com/kms/latest/developerguide/key-state.html">How
         * Key State Affects Use of a Customer Master Key</a> in the <i>AWS Key Management
         * Service Developer Guide</i>.</p><p><h3>See Also:</h3>   <a
         * href="http://docs.aws.amazon.com/goto/WebAPI/kms-2014-11-01/UpdateKeyDescription">AWS
         * API Reference</a></p>
         *
         * Queues the request into a thread executor and triggers associated callback when operation has finished.
         */
        virtual void UpdateKeyDescriptionAsync(const Model::UpdateKeyDescriptionRequest& request, const UpdateKeyDescriptionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context = nullptr) const;

      
      void OverrideEndpoint(const Aws::String& endpoint);
    private:
      void init(const Aws::Client::ClientConfiguration& clientConfiguration);
        /**Async helpers**/
        void CancelKeyDeletionAsyncHelper(const Model::CancelKeyDeletionRequest& request, const CancelKeyDeletionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void ConnectCustomKeyStoreAsyncHelper(const Model::ConnectCustomKeyStoreRequest& request, const ConnectCustomKeyStoreResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void CreateAliasAsyncHelper(const Model::CreateAliasRequest& request, const CreateAliasResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void CreateCustomKeyStoreAsyncHelper(const Model::CreateCustomKeyStoreRequest& request, const CreateCustomKeyStoreResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void CreateGrantAsyncHelper(const Model::CreateGrantRequest& request, const CreateGrantResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void CreateKeyAsyncHelper(const Model::CreateKeyRequest& request, const CreateKeyResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void DecryptAsyncHelper(const Model::DecryptRequest& request, const DecryptResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void DeleteAliasAsyncHelper(const Model::DeleteAliasRequest& request, const DeleteAliasResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void DeleteCustomKeyStoreAsyncHelper(const Model::DeleteCustomKeyStoreRequest& request, const DeleteCustomKeyStoreResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void DeleteImportedKeyMaterialAsyncHelper(const Model::DeleteImportedKeyMaterialRequest& request, const DeleteImportedKeyMaterialResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void DescribeCustomKeyStoresAsyncHelper(const Model::DescribeCustomKeyStoresRequest& request, const DescribeCustomKeyStoresResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void DescribeKeyAsyncHelper(const Model::DescribeKeyRequest& request, const DescribeKeyResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void DisableKeyAsyncHelper(const Model::DisableKeyRequest& request, const DisableKeyResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void DisableKeyRotationAsyncHelper(const Model::DisableKeyRotationRequest& request, const DisableKeyRotationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void DisconnectCustomKeyStoreAsyncHelper(const Model::DisconnectCustomKeyStoreRequest& request, const DisconnectCustomKeyStoreResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void EnableKeyAsyncHelper(const Model::EnableKeyRequest& request, const EnableKeyResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void EnableKeyRotationAsyncHelper(const Model::EnableKeyRotationRequest& request, const EnableKeyRotationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void EncryptAsyncHelper(const Model::EncryptRequest& request, const EncryptResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void GenerateDataKeyAsyncHelper(const Model::GenerateDataKeyRequest& request, const GenerateDataKeyResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void GenerateDataKeyWithoutPlaintextAsyncHelper(const Model::GenerateDataKeyWithoutPlaintextRequest& request, const GenerateDataKeyWithoutPlaintextResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void GenerateRandomAsyncHelper(const Model::GenerateRandomRequest& request, const GenerateRandomResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void GetKeyPolicyAsyncHelper(const Model::GetKeyPolicyRequest& request, const GetKeyPolicyResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void GetKeyRotationStatusAsyncHelper(const Model::GetKeyRotationStatusRequest& request, const GetKeyRotationStatusResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void GetParametersForImportAsyncHelper(const Model::GetParametersForImportRequest& request, const GetParametersForImportResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void ImportKeyMaterialAsyncHelper(const Model::ImportKeyMaterialRequest& request, const ImportKeyMaterialResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void ListAliasesAsyncHelper(const Model::ListAliasesRequest& request, const ListAliasesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void ListGrantsAsyncHelper(const Model::ListGrantsRequest& request, const ListGrantsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void ListKeyPoliciesAsyncHelper(const Model::ListKeyPoliciesRequest& request, const ListKeyPoliciesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void ListKeysAsyncHelper(const Model::ListKeysRequest& request, const ListKeysResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void ListResourceTagsAsyncHelper(const Model::ListResourceTagsRequest& request, const ListResourceTagsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void ListRetirableGrantsAsyncHelper(const Model::ListRetirableGrantsRequest& request, const ListRetirableGrantsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void PutKeyPolicyAsyncHelper(const Model::PutKeyPolicyRequest& request, const PutKeyPolicyResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void ReEncryptAsyncHelper(const Model::ReEncryptRequest& request, const ReEncryptResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void RetireGrantAsyncHelper(const Model::RetireGrantRequest& request, const RetireGrantResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void RevokeGrantAsyncHelper(const Model::RevokeGrantRequest& request, const RevokeGrantResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void ScheduleKeyDeletionAsyncHelper(const Model::ScheduleKeyDeletionRequest& request, const ScheduleKeyDeletionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void TagResourceAsyncHelper(const Model::TagResourceRequest& request, const TagResourceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void UntagResourceAsyncHelper(const Model::UntagResourceRequest& request, const UntagResourceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void UpdateAliasAsyncHelper(const Model::UpdateAliasRequest& request, const UpdateAliasResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void UpdateCustomKeyStoreAsyncHelper(const Model::UpdateCustomKeyStoreRequest& request, const UpdateCustomKeyStoreResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;
        void UpdateKeyDescriptionAsyncHelper(const Model::UpdateKeyDescriptionRequest& request, const UpdateKeyDescriptionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const;

      Aws::String m_uri;
      Aws::String m_configScheme;
      std::shared_ptr<Aws::Utils::Threading::Executor> m_executor;
  };

} // namespace KMS
} // namespace Aws