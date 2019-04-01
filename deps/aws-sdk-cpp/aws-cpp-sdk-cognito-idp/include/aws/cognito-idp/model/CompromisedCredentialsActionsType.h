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
#include <aws/cognito-idp/CognitoIdentityProvider_EXPORTS.h>
#include <aws/cognito-idp/model/CompromisedCredentialsEventActionType.h>
#include <utility>

namespace Aws
{
namespace Utils
{
namespace Json
{
  class JsonValue;
  class JsonView;
} // namespace Json
} // namespace Utils
namespace CognitoIdentityProvider
{
namespace Model
{

  /**
   * <p>The compromised credentials actions type</p><p><h3>See Also:</h3>   <a
   * href="http://docs.aws.amazon.com/goto/WebAPI/cognito-idp-2016-04-18/CompromisedCredentialsActionsType">AWS
   * API Reference</a></p>
   */
  class AWS_COGNITOIDENTITYPROVIDER_API CompromisedCredentialsActionsType
  {
  public:
    CompromisedCredentialsActionsType();
    CompromisedCredentialsActionsType(Aws::Utils::Json::JsonView jsonValue);
    CompromisedCredentialsActionsType& operator=(Aws::Utils::Json::JsonView jsonValue);
    Aws::Utils::Json::JsonValue Jsonize() const;


    /**
     * <p>The event action.</p>
     */
    inline const CompromisedCredentialsEventActionType& GetEventAction() const{ return m_eventAction; }

    /**
     * <p>The event action.</p>
     */
    inline bool EventActionHasBeenSet() const { return m_eventActionHasBeenSet; }

    /**
     * <p>The event action.</p>
     */
    inline void SetEventAction(const CompromisedCredentialsEventActionType& value) { m_eventActionHasBeenSet = true; m_eventAction = value; }

    /**
     * <p>The event action.</p>
     */
    inline void SetEventAction(CompromisedCredentialsEventActionType&& value) { m_eventActionHasBeenSet = true; m_eventAction = std::move(value); }

    /**
     * <p>The event action.</p>
     */
    inline CompromisedCredentialsActionsType& WithEventAction(const CompromisedCredentialsEventActionType& value) { SetEventAction(value); return *this;}

    /**
     * <p>The event action.</p>
     */
    inline CompromisedCredentialsActionsType& WithEventAction(CompromisedCredentialsEventActionType&& value) { SetEventAction(std::move(value)); return *this;}

  private:

    CompromisedCredentialsEventActionType m_eventAction;
    bool m_eventActionHasBeenSet;
  };

} // namespace Model
} // namespace CognitoIdentityProvider
} // namespace Aws