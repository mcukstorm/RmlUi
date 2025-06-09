/*
 * This source file is part of RmlUi, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://github.com/mikke89/RmlUi
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 * Copyright (c) 2019-2024 The RmlUi Team, and contributors
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
#include "../Common/TestsShell.h"
#include <RmlUi/Core/Core.h>
#include <RmlUi/Core/StreamMemory.h>
#include <RmlUi/Core/StyleSheet.h>
#include <RmlUi/Core/StyleSheetContainer.h>
#include <doctest.h>
#include <muParser.h>

static const char stylesheet_calc[] = R"(
body {
	font-family: LatoLatin;
	font-weight: normal;
	font-style: normal;
}
.test {
	padding-left: calc(100%/3 - 2*1em + 2*1px);
	margin: calc(100%/3 - 2*1em + 2*1px) calc(100%/3 - 2*1em - 2*2px) calc(100%/3 - 2*1em - 2*3px) calc(100%/3 - 2*1em - 2*4px);
}
)";

using namespace Rml;

float passthrough_function(float x) {
	return x;
};

TEST_CASE("style_sheet_parser.calc")
{

	Context* context = TestsShell::GetContext();

	{
		StyleSheetContainer style_sheet_container;
		StreamMemory stylesheet_stream{reinterpret_cast<const byte*>(stylesheet_calc), sizeof(stylesheet_calc) - 1};
		style_sheet_container.LoadStyleSheetContainer(&stylesheet_stream, 0);

		style_sheet_container.UpdateCompiledStyleSheet(context);
		const auto* style_sheet = style_sheet_container.GetCompiledStyleSheet();
		CHECK(style_sheet != nullptr);

		try
		{
			float var_a = 2;

			mu::Parser p;
			p.DefineVar("a", &var_a);
			p.DefineConst("e", 2.7182818284590452354);
			p.DefineConst("pi", 3.1415926535897932);
			p.DefineConst("infinity", std::numeric_limits<float>::max());
			p.DefineFun("calc", passthrough_function);
			p.DefinePostfixOprt("%", [](float value){return value;});
			p.DefinePostfixOprt("px", [](float value){return value;});
			p.DefinePostfixOprt("dp", [](float value){return value;});
			p.DefinePostfixOprt("x", [](float value){return value;});
			p.DefinePostfixOprt("vw", [](float value){return value;});
			p.DefinePostfixOprt("vh", [](float value){return value;});
			p.DefinePostfixOprt("em", [](float value){return value;});
			p.DefinePostfixOprt("rem", [](float value){return value;});
			p.DefinePostfixOprt("in", [](float value){return value;});
			p.DefinePostfixOprt("cm", [](float value){return value;});
			p.DefinePostfixOprt("mm", [](float value){return value;});
			p.DefinePostfixOprt("pt", [](float value){return value;});
			p.DefinePostfixOprt("pc", [](float value){return value;});
			//p.DefinePostfixOprt("deg", [](float value){return value;});
			//p.DefinePostfixOprt("rad", [](float value){return value;});

			//p.DefineFun("MySqr", MySqr);
			p.SetExpr("10*pi");
			FAIL("muparser Result: " << p.Eval());
		}
		catch (mu::Parser::exception_type &e)
		{
			FAIL("muparser error: " << e.GetMsg());
		}

	}

	TestsShell::ShutdownShell();
}

