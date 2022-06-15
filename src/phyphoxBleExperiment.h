#ifndef PHYPHOX_BLE_EXPERIMENT
#define PHYPHOX_BLE_EXPERIMENT

#define phyphoxBleNViews 15
#define phyphoxBleNElements 20
#define phyphoxBleNExportSets 10
#define phyphoxBleNChannel 5

#include <Arduino.h>
#include "copyToMem.h"

class PhyphoxBleExperiment {

	public:

	PhyphoxBleExperiment() = default;                     
	PhyphoxBleExperiment(const PhyphoxBleExperiment&) = delete;         
	PhyphoxBleExperiment &operator=(const PhyphoxBleExperiment &) = delete;
	~PhyphoxBleExperiment() = default;

	static uint16_t MTU;

	class Error {
	public:
		char* MESSAGE = NULL;
		void getBytes(char *);
	};


	class Errorhandler {
	public:
		virtual Error err_checkLength(const char *, int, const char *);
		virtual Error err_checkUpper(int, int, const char *);
		virtual Error err_checkHex(const char *, const char *);
		virtual Error err_checkStyle(const char *, const char *);
	};

	class Element : public Errorhandler {
	public:
		Element() = default;
		Element(const Element &) = delete;
		Element &operator=(const Element &) = delete;
		~Element() = default;

		int typeID = 0;

		char LABEL[50] = " label=\"label\"";

		Error ERROR;

		virtual void setLabel(const char *);
		virtual void getBytes(char *)=0;

	private:
	};

	class Channel
	{
	public:
		Channel() = default;
		Channel(const Channel &) = delete;
		Channel &operator=(const Channel &) = delete;
		~Channel() = default;

		char* CHANNELX = NULL;
		char* CHANNELY = NULL;
		char* COLOR   = NULL;
		bool isActive = false;

		void getBytes(char *);
	private:
	};

	class Graph : public Element
	{
	public:
		Graph() = default;
		Graph(const Graph &) = delete;
		Graph &operator=(const Graph &) = delete;
		~Graph() = default;

		char* UNITX = NULL;
		char* UNITY = NULL;
		char* LABELX = NULL;
		char* LABELY = NULL;
		char* COLOR = NULL;
		char* XPRECISION = NULL;
		char* YPRECISION = NULL;

		char* INPUTX = NULL;
		char* INPUTY = NULL;

		Channel CHANNEL[phyphoxBleNChannel];

		char* STYLE = NULL;

		char* XMLAttribute = NULL;

		void setUnitX(const char *);
		void setUnitY(const char *);
		void setLabelX(const char *);
		void setLabelY(const char *);
		void setXPrecision(int);
		void setYPrecision(int);
		void setColor(const char *);
		void setChannel(int, int);
		void addChannel(int, int, const char*);
		void setStyle(const char *);
		void setXMLAttribute(const char *);

		void phyphoxTimestamp();
		void getBytes(char *);

	private:
	};

	class View
	{
	public:
		View() = default;
		View(const View &) = delete;
		View &operator=(const View &) = delete;
		~View() = default;

		void setLabel(const char *);
		void getBytes(char *, uint8_t);
		void addElement(Element &);
		void setXMLAttribute(const char *);

		char* LABEL = NULL;
		char* XMLAttribute = NULL;

		Element *ELEMENTS[phyphoxBleNElements] = {nullptr};

	private:
	};

	class ExportData : public Element
	{
	public:
		ExportData(){};
		ExportData(const ExportData &) = delete;
		ExportData &operator=(const ExportData &) = delete;
		~ExportData() = default;

		char* BUFFER = NULL;
		char* XMLAttribute = NULL;
		void setDatachannel(int);
		void setXMLAttribute(const char *);
		void setLabel(const char *);
		void getBytes(char *);

	private:
	};

	class ExportSet
	{
	public:
		ExportSet(){};
		ExportSet(const ExportSet &) = delete;
		ExportSet &operator=(const ExportSet &) = delete;
		~ExportSet() = default;

		void setLabel(const char *);
		void getBytes(char *);
		void addElement(Element &);
		void setXMLAttribute(const char *);

		char* LABEL = NULL;
		char* XMLAttribute = NULL;
		Element *ELEMENTS[phyphoxBleNExportSets] = {nullptr};

	private:
	};

	class InfoField : public Element
	{
	public:
		InfoField(){};
		InfoField(const InfoField &) = delete;
		InfoField &operator=(const InfoField &) = delete;
		~InfoField() = default;

		void setInfo(const char *);
		void setColor(const char *);
		void setXMLAttribute(const char *);
		void getBytes(char *);

		char* INFO = NULL;
		char* COLOR = NULL;
		char* XMLAttribute = NULL;

	private:
	};

	class Separator : public Element
	{
	public:
		Separator(){};
		Separator(const Separator &) = delete;
		Separator &operator=(const Separator &) = delete;
		~Separator() = default;

		void setHeight(float);
		void setColor(const char *);
		void setXMLAttribute(const char *);
		void getBytes(char *);

		char* COLOR = NULL;
		char* HEIGHT = NULL;
		char* XMLAttribute = NULL;

	private:
	};

	class Value : public Element
	{
	public:
		Value(){};
		Value(const Value &) = delete;
		Value &operator=(const Value &) = delete;
		~Value() = default;

		void setPrecision(int);
		void setUnit(const char *);
		void setColor(const char *);
		void getBytes(char *);
		void setChannel(int);
		void setXMLAttribute(const char *);

		char* PRECISION = NULL;
		char* UNIT = NULL;
		char* COLOR = NULL;
		char* INPUTVALUE = NULL;
		char* XMLAttribute = NULL;

	private:
	};

	class Edit : public Element
	{
	public:
		Edit(){};
		Edit(const Edit &) = delete;
		Edit &operator=(const Edit &) = delete;
		~Edit() = default;

		void setUnit(const char *);
		void setSigned(bool);
		void setDecimal(bool);
		void setXMLAttribute(const char *);
		void setChannel(int);
		void getBytes(char *);

		char* UNIT = NULL;
		char* SIGNED = NULL;
		char* DECIMAL = NULL;
		char* XMLAttribute = NULL;
		char* BUFFER = NULL;
	
	private:
	};

	void setTitle(const char *);
	void setCategory(const char *);
	void setDescription(const char *);
	// void setConfig(const char *);
	void setSubscribeOnStart(bool);

	void getBytes(char *);
	void getFirstBytes(char *, const char *);
	void getViewBytes(char *, uint8_t, uint8_t);
	void getLastBytes(char *);
	void addView(View &);
	void addExportSet(ExportSet &);

	char* TITLE = NULL;
	char* CATEGORY = NULL;
	char* DESCRIPTION = NULL;
	// char* CONFIG = NULL;
	char* SUBSCRIBEONSTART = NULL;

	View *VIEWS[phyphoxBleNViews] = {nullptr};
	ExportSet *EXPORTSETS[phyphoxBleNExportSets] = {nullptr};

	static int numberOfChannels;
	int repeating = 0;

	
};

#endif
