function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <S1>/MPComSend */
	this.urlHashMap["FullDuplex_UDP:93"] = "FullDuplex_UDP.c:106,133&FullDuplex_UDP.h:65,68&FullDuplex_UDP_data.c:41,44";
	/* <S1>/Pack */
	this.urlHashMap["FullDuplex_UDP:94"] = "FullDuplex_UDP.c:98,100&FullDuplex_UDP.h:50,52";
	/* <S1>/Unpack */
	this.urlHashMap["FullDuplex_UDP:95"] = "FullDuplex_UDP.c:81,83&FullDuplex_UDP.h:47,48";
	/* <S2>/DebugPrint2_sfcn */
	this.urlHashMap["FullDuplex_UDP:90:129"] = "FullDuplex_UDP.c:95&FullDuplex_UDP.h:74&FullDuplex_UDP_data.c:51";
	/* <S2>/Pack */
	this.urlHashMap["FullDuplex_UDP:90:130"] = "FullDuplex_UDP.c:87,89&FullDuplex_UDP.h:49,51";
	/* <S3>/Enabled
Subsystem */
	this.urlHashMap["FullDuplex_UDP:92:120"] = "FullDuplex_UDP.c:69,79,137,144";
	/* <S3>/S-Function */
	this.urlHashMap["FullDuplex_UDP:92:124"] = "FullDuplex_UDP.c:64,78,129&FullDuplex_UDP.h:59,62&FullDuplex_UDP_data.c:35,38";
	/* <S4>/In1 */
	this.urlHashMap["FullDuplex_UDP:92:121"] = "FullDuplex_UDP.c:65&FullDuplex_UDP.h:53";
	/* <S4>/Enable */
	this.urlHashMap["FullDuplex_UDP:92:122"] = "FullDuplex_UDP.c:70";
	/* <S4>/Out1 */
	this.urlHashMap["FullDuplex_UDP:92:123"] = "FullDuplex_UDP.c:138,143&FullDuplex_UDP.h:71&FullDuplex_UDP_data.c:47";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "FullDuplex_UDP"};
	this.sidHashMap["FullDuplex_UDP"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>"] = {sid: "FullDuplex_UDP:87"};
	this.sidHashMap["FullDuplex_UDP:87"] = {rtwname: "<S1>"};
	this.rtwnameHashMap["<S2>"] = {sid: "FullDuplex_UDP:90"};
	this.sidHashMap["FullDuplex_UDP:90"] = {rtwname: "<S2>"};
	this.rtwnameHashMap["<S3>"] = {sid: "FullDuplex_UDP:92"};
	this.sidHashMap["FullDuplex_UDP:92"] = {rtwname: "<S3>"};
	this.rtwnameHashMap["<S4>"] = {sid: "FullDuplex_UDP:92:120"};
	this.sidHashMap["FullDuplex_UDP:92:120"] = {rtwname: "<S4>"};
	this.rtwnameHashMap["<Root>/UDP RECEIVE"] = {sid: "FullDuplex_UDP:87"};
	this.sidHashMap["FullDuplex_UDP:87"] = {rtwname: "<Root>/UDP RECEIVE"};
	this.rtwnameHashMap["<S1>/Advanced Debug Print"] = {sid: "FullDuplex_UDP:90"};
	this.sidHashMap["FullDuplex_UDP:90"] = {rtwname: "<S1>/Advanced Debug Print"};
	this.rtwnameHashMap["<S1>/Demux"] = {sid: "FullDuplex_UDP:91"};
	this.sidHashMap["FullDuplex_UDP:91"] = {rtwname: "<S1>/Demux"};
	this.rtwnameHashMap["<S1>/MPComRecv"] = {sid: "FullDuplex_UDP:92"};
	this.sidHashMap["FullDuplex_UDP:92"] = {rtwname: "<S1>/MPComRecv"};
	this.rtwnameHashMap["<S1>/MPComSend"] = {sid: "FullDuplex_UDP:93"};
	this.sidHashMap["FullDuplex_UDP:93"] = {rtwname: "<S1>/MPComSend"};
	this.rtwnameHashMap["<S1>/Pack"] = {sid: "FullDuplex_UDP:94"};
	this.sidHashMap["FullDuplex_UDP:94"] = {rtwname: "<S1>/Pack"};
	this.rtwnameHashMap["<S1>/Unpack"] = {sid: "FullDuplex_UDP:95"};
	this.sidHashMap["FullDuplex_UDP:95"] = {rtwname: "<S1>/Unpack"};
	this.rtwnameHashMap["<S1>/X"] = {sid: "FullDuplex_UDP:96"};
	this.sidHashMap["FullDuplex_UDP:96"] = {rtwname: "<S1>/X"};
	this.rtwnameHashMap["<S1>/Y"] = {sid: "FullDuplex_UDP:97"};
	this.sidHashMap["FullDuplex_UDP:97"] = {rtwname: "<S1>/Y"};
	this.rtwnameHashMap["<S2>/VarIn1"] = {sid: "FullDuplex_UDP:90:127"};
	this.sidHashMap["FullDuplex_UDP:90:127"] = {rtwname: "<S2>/VarIn1"};
	this.rtwnameHashMap["<S2>/VarIn2"] = {sid: "FullDuplex_UDP:90:128"};
	this.sidHashMap["FullDuplex_UDP:90:128"] = {rtwname: "<S2>/VarIn2"};
	this.rtwnameHashMap["<S2>/DebugPrint2_sfcn"] = {sid: "FullDuplex_UDP:90:129"};
	this.sidHashMap["FullDuplex_UDP:90:129"] = {rtwname: "<S2>/DebugPrint2_sfcn"};
	this.rtwnameHashMap["<S2>/Pack"] = {sid: "FullDuplex_UDP:90:130"};
	this.sidHashMap["FullDuplex_UDP:90:130"] = {rtwname: "<S2>/Pack"};
	this.rtwnameHashMap["<S3>/Enabled Subsystem"] = {sid: "FullDuplex_UDP:92:120"};
	this.sidHashMap["FullDuplex_UDP:92:120"] = {rtwname: "<S3>/Enabled Subsystem"};
	this.rtwnameHashMap["<S3>/S-Function"] = {sid: "FullDuplex_UDP:92:124"};
	this.sidHashMap["FullDuplex_UDP:92:124"] = {rtwname: "<S3>/S-Function"};
	this.rtwnameHashMap["<S3>/Out1"] = {sid: "FullDuplex_UDP:92:125"};
	this.sidHashMap["FullDuplex_UDP:92:125"] = {rtwname: "<S3>/Out1"};
	this.rtwnameHashMap["<S4>/In1"] = {sid: "FullDuplex_UDP:92:121"};
	this.sidHashMap["FullDuplex_UDP:92:121"] = {rtwname: "<S4>/In1"};
	this.rtwnameHashMap["<S4>/Enable"] = {sid: "FullDuplex_UDP:92:122"};
	this.sidHashMap["FullDuplex_UDP:92:122"] = {rtwname: "<S4>/Enable"};
	this.rtwnameHashMap["<S4>/Out1"] = {sid: "FullDuplex_UDP:92:123"};
	this.sidHashMap["FullDuplex_UDP:92:123"] = {rtwname: "<S4>/Out1"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
