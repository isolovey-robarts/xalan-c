/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 1999-2002 The Apache Software Foundation.  All rights 
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:  
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Xalan" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written 
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation and was
 * originally based on software copyright (c) 1999, International
 * Business Machines, Inc., http://www.ibm.com.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */
#if !defined(XALAN_SelectionEvent_HEADER_GUARD)
#define XALAN_SelectionEvent_HEADER_GUARD



// Base include file.  Must be first.
#include <XSLT/XSLTDefinitions.hpp>



#include <XalanDOM/XalanDOMString.hpp>



#include <XPath/XObject.hpp>



XALAN_CPP_NAMESPACE_BEGIN



class XalanNode;
class ElemTemplateElement;
class StylesheetExecutionContext;
class XPath;



class XALAN_XSLT_EXPORT SelectionEvent
{
public:

	/**
	 * Create an event originating at the given node of the style tree.
	 *
	 * @param executionContext The current execution context
	 * @param sourceNode The source node selected.
	 * @param styleNode The node in the style tree reference for the event
	 * @param attributeName The attribute name where the XPath expression was supplied
	 * @param xpath The XPath instance executed
	 * @param selection The result of evaluating the XPath
	 *
	 */
	SelectionEvent(
			StylesheetExecutionContext&		executionContext,
			const XalanNode*				sourceNode,
			const ElemTemplateElement&		styleNode,
			const XalanDOMString&			attributeName,
			const XPath&					xpath,
			const XObjectPtr				selection);

	/**
	 * Create an event originating at the given node of the style tree.
	 *
	 * @param executionContext The current execution context
	 * @param sourceNode The source node selected.
	 * @param styleNode The node in the style tree reference for the event
	 * @param attributeName The attribute name where the XPath expression was supplied
	 * @param xpathExpression The XPath expression executed
	 * @param selection The result of evaluating the XPath
	 *
	 */
	SelectionEvent(
			StylesheetExecutionContext&		executionContext,
			const XalanNode*				sourceNode,
			const ElemTemplateElement&		styleNode,
			const XalanDOMString&			attributeName,
			const XalanDOMString&			xpathExpression,
			const XObjectPtr				selection);

	virtual
	~SelectionEvent();

	/**
	 * The executionContext instance.
	 */
	const StylesheetExecutionContext&	m_executionContext;

	/**
	 * The current context node.
	 */
	const XalanNode*					m_sourceNode;
  
	/**
	 * The node in the style tree where the event occurs.
	 */
	const ElemTemplateElement&			m_styleNode;

	/**
	 * The attribute name from which the selection is made.
	 */
	const XalanDOMString&				m_attributeName;

	/**
	 * The XPath expression evaluated.
	 */
	const XalanDOMString&				m_xpathExpression;
  
	/**
	 * The result of the selection.  If it's null, m_sourceNode
	 * was selected.
	 */
	const XObjectPtr					m_selection;

private:

	// Unimplemented...
	SelectionEvent&
	operator=(const SelectionEvent&	other);
};



XALAN_CPP_NAMESPACE_END



#endif	//XALAN_SelectionEvent_HEADER_GUARD
