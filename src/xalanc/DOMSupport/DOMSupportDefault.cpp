/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 1999-2004 The Apache Software Foundation.  All rights 
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
#include "DOMSupportDefault.hpp"



#include <vector>



#include <xalanc/XalanDOM/XalanNode.hpp>
#include <xalanc/XalanDOM/XalanAttr.hpp>
#include <xalanc/XalanDOM/XalanDocument.hpp>
#include <xalanc/XalanDOM/XalanDocumentType.hpp>
#include <xalanc/XalanDOM/XalanElement.hpp>
#include <xalanc/XalanDOM/XalanEntity.hpp>
#include <xalanc/XalanDOM/XalanNamedNodeMap.hpp>



#include <xalanc/PlatformSupport/DOMStringHelper.hpp>
#include "DOMServices.hpp"
#include "DOMSupportException.hpp"



XALAN_CPP_NAMESPACE_BEGIN



DOMSupportDefault::DOMSupportDefault() :
	DOMSupport(),
	m_pool()
{
}



DOMSupportDefault::~DOMSupportDefault()
{
}



void
DOMSupportDefault::reset()
{
}



const XalanDOMString&
DOMSupportDefault::getUnparsedEntityURI(
			const XalanDOMString&	theName,
			const XalanDocument&	theDocument) const
{
	XalanDOMString					theURI;

	const XalanDocumentType* const	theDoctype =
		theDocument.getDoctype();

	if(theDoctype != 0)
	{
		const XalanNamedNodeMap* const	theEntities =
			theDoctype->getEntities();

		if (theEntities != 0)
		{
			const XalanNode* const	theNode =
				theEntities->getNamedItem(theName);

			if (theNode != 0 && theNode->getNodeType() == XalanNode::ENTITY_NODE)
			{
				const XalanEntity*	theEntity =
#if defined(XALAN_OLD_STYLE_CASTS)
					(const XalanEntity*)theNode;
#else
					static_cast<const XalanEntity*>(theNode);
#endif

				const XalanDOMString		theNotationName(theEntity->getNotationName());

				if(isEmpty(theNotationName) == false) // then it's unparsed
				{
					// The draft says: "The XSLT processor may use the public
					// identifier to generate a URI for the entity instead of the URI
					// specified in the system identifier. If the XSLT processor does
					// not use the public identifier to generate the URI, it must use
					// the system identifier; if the system identifier is a relative
					// URI, it must be resolved into an absolute URI using the URI of
					// the resource containing the entity declaration as the base
					// URI [RFC2396]."
					// So I'm falling a bit short here.
					theURI = theEntity->getSystemId();

					if(isEmpty(theURI) == true)
					{
						theURI = theEntity->getPublicId();
					}
					else
					{
						// This should be resolved to an absolute URL, but that's hard
						// to do from here.
					}
				}
			}
		}
	}

#if defined(XALAN_NO_MUTABLE)
	return ((DOMSupportDefault*)this)->m_pool.get(theURI);
#else
	return m_pool.get(theURI);
#endif
}



bool
DOMSupportDefault::isNodeAfter(
			const XalanNode&	node1,
			const XalanNode&	node2) const
{
	return DOMServices::isNodeAfter(node1, node2);
}



XALAN_CPP_NAMESPACE_END