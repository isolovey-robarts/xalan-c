/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2000 The Apache Software Foundation.  All rights 
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
#if !defined(XALANDEFAULTPARSEDSOURCE_HEADER_GUARD)
#define XALANDEFAULTPARSEDSOURCE_HEADER_GUARD



// Base include file.  Must be first.
#include <XalanTransformer/XalanTransformerDefinitions.hpp>



#include <XalanSourceTree/XalanSourceTreeParserLiaison.hpp>
#include <XalanSourceTree/XalanSourceTreeDOMSupport.hpp>



#include <XSLT/XSLTInputSource.hpp>



#include <XalanTransformer/XalanParsedSource.hpp>



class EntityResolver;
class ErrorHandler;
class XalanSourceTreeDocument;



class XalanDefaultParsedSourceDOMSupport : public XalanSourceTreeDOMSupport
{
public:

	XalanDefaultParsedSourceDOMSupport(const XalanSourceTreeDOMSupport&		theDOMSupport);

	virtual
	~XalanDefaultParsedSourceDOMSupport();

	virtual void
	reset();

	// These interfaces are inherited from DOMSupport...

	virtual const XalanDOMString*
	getNamespaceForPrefix(
			const XalanDOMString&	prefix, 
			const XalanElement&		namespaceContext) const;

	virtual const XalanDOMString&
	getUnparsedEntityURI(
			const XalanDOMString&	theName,
			const XalanDocument&	theDocument) const;

	virtual bool
	isNodeAfter(
			const XalanNode&	node1,
			const XalanNode&	node2) const;

private:

	const XalanSourceTreeDOMSupport&	m_domSupport;
};



class XALAN_TRANSFORMER_EXPORT XalanDefaultParsedSourceHelper : public XalanParsedSourceHelper
{
public:

	XalanDefaultParsedSourceHelper(
			const XalanSourceTreeDOMSupport&		theSourceDOMSupport,
			const XalanSourceTreeParserLiaison&		theSourceParserLiaison);

	virtual DOMSupport&
	getDOMSupport();

	virtual XMLParserLiaison&
	getParserLiaison();

private:

	XalanDefaultParsedSourceDOMSupport	m_domSupport;

	XalanSourceTreeParserLiaison		m_parserLiaison;
};



/**
 * This is designed to allow a XalanTranfomer object to reuse a parsed
 * document. 
 */
class XALAN_TRANSFORMER_EXPORT XalanDefaultParsedSource : public XalanParsedSource
{
public:

	XalanDefaultParsedSource(
			const XSLTInputSource&	theInputSource,
			bool					fValidate = false,
			ErrorHandler*			theErrorHandler = 0,
			EntityResolver*			theEntityResolver = 0);

	virtual
	~XalanDefaultParsedSource();

	virtual XalanDocument*
	getDocument() const;

	virtual XalanParsedSourceHelper*
	createHelper() const;

	virtual const XalanDOMString&
	getURI() const;

private:

	XalanSourceTreeDOMSupport		m_domSupport;

	XalanSourceTreeParserLiaison	m_parserLiaison;

	XalanSourceTreeDocument*		m_parsedSource;

	XalanDOMString					m_uri;
};



#endif	// XALANDEFAULTPARSEDSOURCE_HEADER_GUARD



