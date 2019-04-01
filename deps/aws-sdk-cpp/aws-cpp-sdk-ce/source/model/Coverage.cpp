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

#include <aws/ce/model/Coverage.h>
#include <aws/core/utils/json/JsonSerializer.h>

#include <utility>

using namespace Aws::Utils::Json;
using namespace Aws::Utils;

namespace Aws
{
namespace CostExplorer
{
namespace Model
{

Coverage::Coverage() : 
    m_coverageHoursHasBeenSet(false),
    m_coverageNormalizedUnitsHasBeenSet(false),
    m_coverageCostHasBeenSet(false)
{
}

Coverage::Coverage(JsonView jsonValue) : 
    m_coverageHoursHasBeenSet(false),
    m_coverageNormalizedUnitsHasBeenSet(false),
    m_coverageCostHasBeenSet(false)
{
  *this = jsonValue;
}

Coverage& Coverage::operator =(JsonView jsonValue)
{
  if(jsonValue.ValueExists("CoverageHours"))
  {
    m_coverageHours = jsonValue.GetObject("CoverageHours");

    m_coverageHoursHasBeenSet = true;
  }

  if(jsonValue.ValueExists("CoverageNormalizedUnits"))
  {
    m_coverageNormalizedUnits = jsonValue.GetObject("CoverageNormalizedUnits");

    m_coverageNormalizedUnitsHasBeenSet = true;
  }

  if(jsonValue.ValueExists("CoverageCost"))
  {
    m_coverageCost = jsonValue.GetObject("CoverageCost");

    m_coverageCostHasBeenSet = true;
  }

  return *this;
}

JsonValue Coverage::Jsonize() const
{
  JsonValue payload;

  if(m_coverageHoursHasBeenSet)
  {
   payload.WithObject("CoverageHours", m_coverageHours.Jsonize());

  }

  if(m_coverageNormalizedUnitsHasBeenSet)
  {
   payload.WithObject("CoverageNormalizedUnits", m_coverageNormalizedUnits.Jsonize());

  }

  if(m_coverageCostHasBeenSet)
  {
   payload.WithObject("CoverageCost", m_coverageCost.Jsonize());

  }

  return payload;
}

} // namespace Model
} // namespace CostExplorer
} // namespace Aws