/*
 * This source file is part of RmlUi, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://github.com/mikke89/RmlUi
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 * Copyright (c) 2019-2023 The RmlUi Team, and contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "PropertyParserCalc.h"
#include <muParser.h>

namespace Rml {

struct PropertyParserCalcData {
	const UnorderedMap<String, Unit> unit_string_map = {
		{"", Unit::NUMBER},
		{"%", Unit::PERCENT},
		{"px", Unit::PX},
		{"dp", Unit::DP},
		{"x", Unit::X},
		{"vw", Unit::VW},
		{"vh", Unit::VH},
		{"em", Unit::EM},
		{"rem", Unit::REM},
		{"in", Unit::INCH},
		{"cm", Unit::CM},
		{"mm", Unit::MM},
		{"pt", Unit::PT},
		{"pc", Unit::PC},
		{"deg", Unit::DEG},
		{"rad", Unit::RAD},
	};
};

ControlledLifetimeResource<PropertyParserCalcData> PropertyParserCalc::parser_data;

void PropertyParserCalc::Initialize()
{
	parser_data.Initialize();
}

void PropertyParserCalc::Shutdown()
{
	parser_data.Shutdown();
}

PropertyParserCalc::PropertyParserCalc(Units units, Unit zero_unit) : units(units), zero_unit(zero_unit) {}

PropertyParserCalc::~PropertyParserCalc() {}

char PropertyParserCalc::FindToken(const String& input_string, String& output_buffer, const char* tokens, bool remove_token, int start_position=0)
{
	int parse_buffer_pos = start_position;
	output_buffer.clear();

	while (parse_buffer_pos <= input_string.size())
	{
		if (strchr(tokens, input_string[parse_buffer_pos]) != nullptr)
		{
			if (remove_token)
				parse_buffer_pos++;
			return input_string[parse_buffer_pos];
		}

		output_buffer += input_string[parse_buffer_pos];
		parse_buffer_pos++;
	}

	return 0;
}

bool PropertyParserCalc::ParseValue(Property& property, const String& value, const ParameterMap& /*parameters*/) const
{
	if (!StringUtilities::StartsWith(value, "calc(")) return false;



	return false;
}

} // namespace Rml
