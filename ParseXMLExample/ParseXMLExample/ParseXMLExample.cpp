// ParseXMLExample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <libxml/parser.h>


void parseXMLDomFromFile(const char *file);

int main() {
	LIBXML_TEST_VERSION

	parseXMLDomFromFile("nbrfxrates.xml");

	xmlCleanupParser();

	return 0;
}

static void parseXMLDomFromFile(const char *file) {
	xmlDocPtr document;
	xmlNodePtr root, node, child_node, rate;
	xmlChar *date = NULL;
	xmlChar *currency = NULL;
	xmlChar *exch_rate = NULL;
	xmlChar *multiplier = NULL;

	document = xmlParseFile(file);

	if (document == NULL) {
		fprintf(stderr, "Failed to parse XML from \"%s\".\n", file);
		return;
	}

	root = xmlDocGetRootElement(document);

	if (!root || !root->name) {
		fprintf(stderr, "Failed to parse XML from \"%s\".\n", file);
		goto xmlcleanup;
	}

	for (node = root->children; node != NULL; node = node->next) {
		if (node->type != XML_ELEMENT_NODE || xmlStrcmp(node->name, (xmlChar *)"Body") != 0)
			continue;

		for (child_node = node->children; child_node != NULL; child_node = child_node->next) {
			if (child_node->type != XML_ELEMENT_NODE || xmlStrcmp(child_node->name, (xmlChar *)"Cube") != 0)
				continue;

			date = xmlGetProp(child_node, (xmlChar *)"date");

			if (!date)
				continue;

			for (rate = child_node->children; rate != NULL; rate = rate->next) {
				if (rate->type != XML_ELEMENT_NODE || xmlStrcmp(rate->name, (xmlChar *)"Rate") != 0)
					continue;

				currency = xmlGetProp(rate, (xmlChar *)"currency");
				multiplier = xmlGetProp(rate, (xmlChar *)"multiplier");

				if (!multiplier) {
					multiplier = (xmlChar*)xmlMalloc(2 * sizeof(xmlChar));
					xmlStrPrintf(multiplier, 2, (xmlChar *)"1\0");
				}

				exch_rate = xmlNodeGetContent(rate);

				fprintf(stdout,
					"\t date %s currency=%s multiplier=%s "
					"exch_rate=%s\n",
					date, currency, multiplier,
					exch_rate);

				xmlFree(exch_rate);
				xmlFree(multiplier);
				xmlFree(currency);
			}

			xmlFree(date);
		}
	}

xmlcleanup:
	xmlFreeDoc(document);
}
