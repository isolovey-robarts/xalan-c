/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 1999 The Apache Software Foundation.  All rights 
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
#if !defined(STYLESHEETCONSTRUCTIONCONTEXT_HEADER_GUARD_1357924680)
#define STYLESHEETCONSTRUCTIONCONTEXT_HEADER_GUARD_1357924680



// Base include file.  Must be first.
#include <XSLT/XSLTDefinitions.hpp>



// Base class header file...
#include <PlatformSupport/ExecutionContext.hpp>



#include <dom/DOM_Node.hpp>



class DOMString;
class PrefixResolver;
class XPath;
class XMLURL;



//
// An abstract class which provides support for constructing the internal
// representation  of a stylesheet.
//
class XALAN_XSLT_EXPORT StylesheetConstructionContext : public ExecutionContext
{
public:

	explicit
	StylesheetConstructionContext();

	virtual
	~StylesheetConstructionContext();

	// These interfaces are inherited from ExecutionContext...

	/**
	 * Tell the user of an error, and probably throw an 
	 * exception.
	 */
	virtual void
	error(
			const DOMString&	msg,
			const DOM_Node& 	sourceNode = DOM_Node(),
			const DOM_Node&		styleNode = DOM_Node()) const = 0;

	/**
	 * Tell the user of an warning, and probably throw an 
	 * exception.
	 */
	virtual void
	warn(
			const DOMString&	msg,
			const DOM_Node& 	sourceNode = DOM_Node(),
			const DOM_Node&		styleNode = DOM_Node()) const = 0;

	/**
	 * Output a message.
	 */
	virtual void
	message(
			const DOMString&	msg,
			const DOM_Node& 	sourceNode = DOM_Node(),
			const DOM_Node&		styleNode = DOM_Node()) const = 0;

	virtual int
	getAttrTok(const DOMString&	name) const = 0;

	virtual XMLURL*
	getURLFromString(const DOMString&	urlString) = 0;

	virtual XMLURL*
	getURLFromString(
			const DOMString&	urlString,
			const DOMString&	base) = 0;

	virtual const DOMString&
	getXSLNameSpaceURLPre() const = 0;

	virtual const DOMString&
	getXSLNameSpaceURL() const = 0;

	/**
	 * Create and initialize an xpath and return it.
	 * This is to be used by stylesheet elements that need
	 * an XPath that is guaranteed to persist while it lives.
	 */
	virtual XPath*
	createMatchPattern(
			const DOMString&		str,
			const PrefixResolver&	resolver) = 0;

	/**
	 * Create and initialize an xpath and return it.
	 * This is to be used by stylesheet elements that need
	 * an XPath that is guaranteed to persist while it lives.
	 */
	virtual XPath*
	createXPath(
			const DOMString&		str,
			const PrefixResolver&	resolver) = 0;
};



#endif	// STYLESHEETCONSTRUCTIONCONTEXT_HEADER_GUARD_1357924680
