/*
 * Copyright 1999-2004 The Apache Software Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#if !defined(XALAN_SPACENODETESTER_HEADER_GUARD_1357924680)
#define XALAN_SPACENODETESTER_HEADER_GUARD_1357924680

/**
 * $Id$
 * 
 * $State$
 * 
 */

// Base include file.  Must be first.
#include "XSLTDefinitions.hpp"



#include "xalanc/XPath/XPath.hpp"



XALAN_CPP_NAMESPACE_BEGIN



class PrefixResolver;
class StylesheetConstructionContext;



class XalanSpaceNodeTester
{
public:

    XalanSpaceNodeTester();

    XalanSpaceNodeTester(
            StylesheetConstructionContext&  theContext,
            const XalanDOMString&           theNameTest,
            const PrefixResolver&           thePrefixResolver,
            const LocatorType*              theLocator);

    ~XalanSpaceNodeTester();

    XPath::eMatchScore
    getMatchScore() const
    {
        return m_matchScore;
    }

	XPath::eMatchScore
	operator()(const XalanNode&     context) const
	{
	    return m_nodeTester(context);
	}

private:

    XPath::NodeTester   m_nodeTester;

    XPath::eMatchScore  m_matchScore;
};



XALAN_CPP_NAMESPACE_END



#endif	// !defined(XALAN_SPACENODETESTER_HEADER_GUARD_1357924680)
