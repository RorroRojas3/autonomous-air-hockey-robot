function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/MPComSend */
	this.urlHashMap["FullDuplex_UDP:82"] = "FullDuplex_UDP.c:106,133&FullDuplex_UDP.h:65,68&FullDuplex_UDP_data.c:41,44";
	/* <Root>/Pack */
	this.urlHashMap["FullDuplex_UDP:83"] = "FullDuplex_UDP.c:98,100&FullDuplex_UDP.h:50,52";
	/* <Root>/Unpack */
	this.urlHashMap["FullDuplex_UDP:86"] = "FullDuplex_UDP.c:81,83&FullDuplex_UDP.h:47,48";
	/* <S1>/DebugPrint2_sfcn */
	this.urlHashMap["FullDuplex_UDP:77:129"] = "FullDuplex_UDP.c:95&FullDuplex_UDP.h:74&FullDuplex_UDP_data.c:51";
	/* <S1>/Pack */
	this.urlHashMap["FullDuplex_UDP:77:130"] = "FullDuplex_UDP.c:87,89&FullDuplex_UDP.h:49,51";
	/* <S2>/Enabled
Subsystem */
	this.urlHashMap["FullDuplex_UDP:81:120"] = "FullDuplex_UDP.c:69,79,137,144";
	/* <S2>/S-Function */
	this.urlHashMap["FullDuplex_UDP:81:124"] = "FullDuplex_UDP.c:64,78,129&FullDuplex_UDP.h:59,62&FullDuplex_UDP_data.c:35,38";
	/* <S3>/In1 */
	this.urlHashMap["FullDuplex_UDP:81:121"] = "FullDuplex_UDP.c:65&FullDuplex_UDP.h:53";
	/* <S3>/Enable */
	this.urlHashMap["FullDuplex_UDP:81:122"] = "FullDuplex_UDP.c:70";
	/* <S3>/Out1 */
	this.urlHashMap["FullDuplex_UDP:81:123"] = "FullDuplex_UDP.c:138,143&FullDuplex_UDP.h:71&FullDuplex_UDP_data.c:47";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "FullDuplex_UDP"};
	this.sidHashMap["FullDuplex_UDP"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>"] = {sid: "FullDuplex_UDP:77"};
	this.sidHashMap["FullDuplex_UDP:77"] = {rtwname: "<S1>"};
	this.rtwnameHashMap["<S2>"] = {sid: "FullDuplex_UDP:81"};
	this.sidHashMap["FullDuplex_UDP:81"] = {rtwname: "<S2>"};
	this.rtwnameHashMap["<S3>"] = {sid: "FullDuplex_UDP:81:120"};
	this.sidHashMap["FullDuplex_UDP:81:120"] = {rtwname: "<S3>"};
	this.rtwnameHashMap["<Root>/Advanced Debug Print"] = {sid: "FullDuplex_UDP:77"};
	this.sidHashMap["FullDuplex_UDP:77"] = {rtwname: "<Root>/Advanced Debug Print"};
	this.rtwnameHashMap["<Root>/Demux"] = {sid: "FullDuplex_UDP:80"};
	this.sidHashMap["FullDuplex_UDP:80"] = {rtwname: "<Root>/Demux"};
	this.rtwnameHashMap["<Root>/MPComRecv"] = {sid: "FullDuplex_UDP:81"};
	this.sidHashMap["FullDuplex_UDP:81"] = {rtwname: "<Root>/MPComRecv"};
	this.rtwnameHashMap["<Root>/MPComSend"] = {sid: "FullDuplex_UDP:82"};
	this.sidHashMap["FullDuplex_UDP:82"] = {rtwname: "<Root>/MPComSend"};
	this.rtwnameHashMap["<Root>/Pack"] = {sid: "FullDuplex_UDP:83"};
	this.sidHashMap["FullDuplex_UDP:83"] = {rtwname: "<Root>/Pack"};
	this.rtwnameHashMap["<Root>/Unpack"] = {sid: "FullDuplex_UDP:86"};
	this.sidHashMap["FullDuplex_UDP:86"] = {rtwname: "<Root>/Unpack"};
	this.rtwnameHashMap["<S1>/VarIn1"] = {sid: "FullDuplex_UDP:77:127"};
	this.sidHashMap["FullDuplex_UDP:77:127"] = {rtwname: "<S1>/VarIn1"};
	this.rtwnameHashMap["<S1>/VarIn2"] = {sid: "FullDuplex_UDP:77:128"};
	this.sidHashMap["FullDuplex_UDP:77:128"] = {rtwname: "<S1>/VarIn2"};
	this.rtwnameHashMap["<S1>/DebugPrint2_sfcn"] = {sid: "FullDuplex_UDP:77:129"};
	this.sidHashMap["FullDuplex_UDP:77:129"] = {rtwname: "<S1>/DebugPrint2_sfcn"};
	this.rtwnameHashMap["<S1>/Pack"] = {sid: "FullDuplex_UDP:77:130"};
	this.sidHashMap["FullDuplex_UDP:77:130"] = {rtwname: "<S1>/Pack"};
	this.rtwnameHashMap["<S2>/Enabled Subsystem"] = {sid: "FullDuplex_UDP:81:120"};
	this.sidHashMap["FullDuplex_UDP:81:120"] = {rtwname: "<S2>/Enabled Subsystem"};
	this.rtwnameHashMap["<S2>/S-Function"] = {sid: "FullDuplex_UDP:81:124"};
	this.sidHashMap["FullDuplex_UDP:81:124"] = {rtwname: "<S2>/S-Function"};
	this.rtwnameHashMap["<S2>/Out1"] = {sid: "FullDuplex_UDP:81:125"};
	this.sidHashMap["FullDuplex_UDP:81:125"] = {rtwname: "<S2>/Out1"};
	this.rtwnameHashMap["<S3>/In1"] = {sid: "FullDuplex_UDP:81:121"};
	this.sidHashMap["FullDuplex_UDP:81:121"] = {rtwname: "<S3>/In1"};
	this.rtwnameHashMap["<S3>/Enable"] = {sid: "FullDuplex_UDP:81:122"};
	this.sidHashMap["FullDuplex_UDP:81:122"] = {rtwname: "<S3>/Enable"};
	this.rtwnameHashMap["<S3>/Out1"] = {sid: "FullDuplex_UDP:81:123"};
	this.sidHashMap["FullDuplex_UDP:81:123"] = {rtwname: "<S3>/Out1"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
