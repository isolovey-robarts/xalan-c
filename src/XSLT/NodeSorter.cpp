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
/**
 * 
 * @author Scott Boag (scott_boag@lotus.com)
 * @author David N. Bertoni (david_n_bertoni@lotus.com)
 */



// Class header file.
#include "NodeSorter.hpp"



#include <PlatformSupport/DOMStringHelper.hpp>
#include <PlatformSupport/DoubleSupport.hpp>



#include <XPath/XObjectFactory.hpp>
#include <XPath/XPath.hpp>



NodeSorter::NodeSorter(XPathExecutionContext&	executionContext) :
	m_executionContext(executionContext),
	m_keys()
{
}



NodeSorter::~NodeSorter()
{
}



void
NodeSorter::sort(
				const MutableNodeRefList&		theList,
				NodeVectorType&					v,
				const NodeSortKeyVectorType&	keys)
{
#if !defined(XALAN_NO_NAMESPACES)
	using std::stable_sort;
#endif

	m_keys = keys;

	NodeSortKeyCompare	theComparer(m_executionContext,
									theList,
									v,
									keys);

	// Use the stl sort algorithm, which will use our compare functor,
	// which returns true if first less than second
	stable_sort(v.begin(),
			    v.end(),
			    theComparer);
}



void
NodeSorter::sort(
			MutableNodeRefList&				theList,
			const NodeSortKeyVectorType&	keys)
{
	const unsigned int	theLength = theList.getLength();

	// Copy the nodes to a vector...
	NodeVectorType	theNodes;

	theNodes.reserve(theLength);

	unsigned int		i = 0;

	for (; i < theLength; ++i)
	{
		theNodes.push_back(theList.item(i));
	}

	// Do the sort...
	sort(
			theList, 
			theNodes,
			keys);
	assert(theNodes.size() ==
				static_cast<NodeVectorType::size_type>(theLength));

	// Copy the nodes back to the list in sorted order.
	theList.clear();

	for (i = 0; i < theLength; ++i)
	{
		theList.addNode(theNodes[i]);
	}

	assert(theList.getLength() == theLength);
}



NodeSorter::NodeSortKeyCompare::result_type
NodeSorter::NodeSortKeyCompare::operator()(
			first_argument_type		theLHS,
			second_argument_type	theRHS,
			unsigned int			theKeyIndex) const
{
	result_type			theResult = false;

	const NodeSortKey&	theKey = m_nodeSortKeys[theKeyIndex];

	const XPath&		xpath = theKey.getSelectPattern();

	const XObjectGuard	r1(
		m_executionContext.getXObjectFactory(),
		xpath.execute(theLHS, theKey.getPrefixResolver(), NodeRefList(), m_executionContext));
	assert(r1.get() != 0);

	const XObjectGuard	r2(
		m_executionContext.getXObjectFactory(),
		xpath.execute(theRHS, theKey.getPrefixResolver(), NodeRefList(), m_executionContext));
	assert(r2.get() != 0);

	// Compare as numbers
	if(theKey.getTreatAsNumbers() == true)
	{
		double	n1Num = r1->num();
		double	n2Num = r2->num();

		const XalanDOMString	r1str(r1->str());
		const XalanDOMString	r2str(r2->str());

		if (DoubleSupport::isNaN(n1Num))
			n1Num = 0.0;

		if (DoubleSupport::isNaN(n2Num))
			n2Num = 0.0;

		if(n1Num == n2Num &&
		  (theKeyIndex + 1 ) < m_nodeSortKeys.size())
		{
			theResult = operator()(theLHS, theRHS, theKeyIndex + 1);
		}
		else
		{
			const double	diff = n1Num - n2Num;

			if (diff == 0.0)
			{
				// The nodes are equal, so if theLHS is
				// before theRHS, return true.
				theResult = isNodeBefore(theLHS, theRHS);
			}
			else if (theKey.getDescending() == true)
			{
				theResult =  diff < 0.0 ? false : true;
			}
			else
			{
				theResult =  diff < 0.0 ? true : false;
			}
		}
	}
	// Compare as strings
	else
	{
		const int	theCompareResult = collationCompare(r1->str(), r2->str());

		if(0 == theCompareResult)
		{
			if ((theKeyIndex + 1 ) < m_nodeSortKeys.size())
			{
				theResult = operator()(theLHS, theRHS, theKeyIndex + 1);
			}
		}
		else
		{
			if (theCompareResult == 0)
			{
				// The nodes are equal, so if theLHS is
				// before theRHS, return true.
				theResult = isNodeBefore(theLHS, theRHS);
			}
			else if (theKey.getDescending() == true)
			{
				theResult = theCompareResult < 0 ? false : true;
			}
			else
			{
				theResult = theCompareResult < 0 ? true : false;
			}
		}
	}

	return theResult;
}



bool
NodeSorter::NodeSortKeyCompare::isNodeBefore(
			const XalanNode*	node1,
			const XalanNode*	node2) const
{
	bool	theResult = true;

	const unsigned int	theLength = m_list.getLength();

	for(unsigned int i = 0; i < theLength; ++i)
	{
		const XalanNode* const	theCurrentNode = m_list.item(i);

		if (theCurrentNode == node1)
		{
			break;
		}
		else if (theCurrentNode == node2)
		{
			theResult = false;

			break;
		}
	}

	return theResult;
}
