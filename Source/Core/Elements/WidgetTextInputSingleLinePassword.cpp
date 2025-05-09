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

#include "WidgetTextInputSingleLinePassword.h"
#include "../../../Include/RmlUi/Core/ElementText.h"

namespace Rml {

WidgetTextInputSingleLinePassword::WidgetTextInputSingleLinePassword(ElementFormControl* parent) : WidgetTextInputSingleLine(parent) {}

void WidgetTextInputSingleLinePassword::TransformValue(String& value)
{
	const size_t character_length = StringUtilities::LengthUTF8(value);
	value.replace(0, value.length(), character_length, '*');
}

int WidgetTextInputSingleLinePassword::DisplayIndexToAttributeIndex(int display_index, const String& attribute_value)
{
	// Transforming from the attribute value to the display value (above) essentially strips away all continuation
	// bytes. Thus, here we effectively count them back in up to the offset.
	return StringUtilities::ConvertCharacterOffsetToByteOffset(attribute_value, display_index);
}

int WidgetTextInputSingleLinePassword::AttributeIndexToDisplayIndex(int attribute_index, const String& attribute_value)
{
	return (int)StringUtilities::LengthUTF8(StringView(attribute_value, 0, (size_t)attribute_index));
}

} // namespace Rml
