function CodeDefine() { 
this.def = new Array();
this.def["IsrOverrun"] = {file: "ert_main_c.html",line:32,type:"var"};
this.def["OverrunFlag"] = {file: "ert_main_c.html",line:33,type:"var"};
this.def["rt_OneStep"] = {file: "ert_main_c.html",line:34,type:"fcn"};
this.def["main"] = {file: "ert_main_c.html",line:51,type:"fcn"};
this.def["FullDuplex_UDP_DW"] = {file: "FullDuplex_UDP_c.html",line:34,type:"var"};
this.def["FullDuplex_UDP_M_"] = {file: "FullDuplex_UDP_c.html",line:37,type:"var"};
this.def["FullDuplex_UDP_M"] = {file: "FullDuplex_UDP_c.html",line:38,type:"var"};
this.def["rate_scheduler"] = {file: "FullDuplex_UDP_c.html",line:46,type:"fcn"};
this.def["FullDuplex_UDP_step"] = {file: "FullDuplex_UDP_c.html",line:59,type:"fcn"};
this.def["FullDuplex_UDP_initialize"] = {file: "FullDuplex_UDP_c.html",line:195,type:"fcn"};
this.def["FullDuplex_UDP_terminate"] = {file: "FullDuplex_UDP_c.html",line:256,type:"fcn"};
this.def["DW_FullDuplex_UDP"] = {file: "FullDuplex_UDP_h.html",line:59,type:"type"};
this.def["P_FullDuplex_UDP"] = {file: "FullDuplex_UDP_types_h.html",line:34,type:"type"};
this.def["RT_MODEL_FullDuplex_UDP"] = {file: "FullDuplex_UDP_types_h.html",line:37,type:"type"};
this.def["FullDuplex_UDP_P"] = {file: "FullDuplex_UDP_data_c.html",line:33,type:"var"};
this.def["MWDSP_EPH_R_R"] = {file: "../../slprj/ert/_sharedutils/html/MWDSP_EPH_R_R_c.html",line:19,type:"fcn"};
this.def["int8_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:47,type:"type"};
this.def["uint8_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:48,type:"type"};
this.def["int16_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:49,type:"type"};
this.def["uint16_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:50,type:"type"};
this.def["int32_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:51,type:"type"};
this.def["uint32_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:52,type:"type"};
this.def["real32_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:53,type:"type"};
this.def["real64_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:54,type:"type"};
this.def["real_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:60,type:"type"};
this.def["time_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:61,type:"type"};
this.def["boolean_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:62,type:"type"};
this.def["int_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:63,type:"type"};
this.def["uint_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:64,type:"type"};
this.def["ulong_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:65,type:"type"};
this.def["char_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:66,type:"type"};
this.def["uchar_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:67,type:"type"};
this.def["byte_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:68,type:"type"};
this.def["creal32_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:78,type:"type"};
this.def["creal64_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:83,type:"type"};
this.def["creal_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:88,type:"type"};
this.def["cint8_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:95,type:"type"};
this.def["cuint8_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:102,type:"type"};
this.def["cint16_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:109,type:"type"};
this.def["cuint16_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:116,type:"type"};
this.def["cint32_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:123,type:"type"};
this.def["cuint32_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:130,type:"type"};
this.def["pointer_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:148,type:"type"};
}
CodeDefine.instance = new CodeDefine();
var testHarnessInfo = {OwnerFileName: "", HarnessOwner: "", HarnessName: "", IsTestHarness: "0"};
var relPathToBuildDir = "../ert_main.c";
var fileSep = "\\";
var isPC = true;
function Html2SrcLink() {
	this.html2SrcPath = new Array;
	this.html2Root = new Array;
	this.html2SrcPath["ert_main_c.html"] = "../ert_main.c";
	this.html2Root["ert_main_c.html"] = "ert_main_c.html";
	this.html2SrcPath["FullDuplex_UDP_c.html"] = "../FullDuplex_UDP.c";
	this.html2Root["FullDuplex_UDP_c.html"] = "FullDuplex_UDP_c.html";
	this.html2SrcPath["FullDuplex_UDP_h.html"] = "../FullDuplex_UDP.h";
	this.html2Root["FullDuplex_UDP_h.html"] = "FullDuplex_UDP_h.html";
	this.html2SrcPath["FullDuplex_UDP_private_h.html"] = "../FullDuplex_UDP_private.h";
	this.html2Root["FullDuplex_UDP_private_h.html"] = "FullDuplex_UDP_private_h.html";
	this.html2SrcPath["FullDuplex_UDP_types_h.html"] = "../FullDuplex_UDP_types.h";
	this.html2Root["FullDuplex_UDP_types_h.html"] = "FullDuplex_UDP_types_h.html";
	this.html2SrcPath["FullDuplex_UDP_data_c.html"] = "../FullDuplex_UDP_data.c";
	this.html2Root["FullDuplex_UDP_data_c.html"] = "FullDuplex_UDP_data_c.html";
	this.html2SrcPath["MWDSP_EPH_R_R_c.html"] = "../MWDSP_EPH_R_R.c";
	this.html2Root["MWDSP_EPH_R_R_c.html"] = "../../slprj/ert/_sharedutils/html/MWDSP_EPH_R_R_c.html";
	this.html2SrcPath["MWDSP_EPH_R_R_h.html"] = "../MWDSP_EPH_R_R.h";
	this.html2Root["MWDSP_EPH_R_R_h.html"] = "../../slprj/ert/_sharedutils/html/MWDSP_EPH_R_R_h.html";
	this.html2SrcPath["rtwtypes_h.html"] = "../rtwtypes.h";
	this.html2Root["rtwtypes_h.html"] = "../../slprj/ert/_sharedutils/html/rtwtypes_h.html";
	this.html2SrcPath["rtmodel_h.html"] = "../rtmodel.h";
	this.html2Root["rtmodel_h.html"] = "rtmodel_h.html";
	this.html2SrcPath["MW_target_hardware_resources_h.html"] = "../MW_target_hardware_resources.h";
	this.html2Root["MW_target_hardware_resources_h.html"] = "MW_target_hardware_resources_h.html";
	this.getLink2Src = function (htmlFileName) {
		 if (this.html2SrcPath[htmlFileName])
			 return this.html2SrcPath[htmlFileName];
		 else
			 return null;
	}
	this.getLinkFromRoot = function (htmlFileName) {
		 if (this.html2Root[htmlFileName])
			 return this.html2Root[htmlFileName];
		 else
			 return null;
	}
}
Html2SrcLink.instance = new Html2SrcLink();
var fileList = [
"ert_main_c.html","FullDuplex_UDP_c.html","FullDuplex_UDP_h.html","FullDuplex_UDP_private_h.html","FullDuplex_UDP_types_h.html","FullDuplex_UDP_data_c.html","MWDSP_EPH_R_R_c.html","MWDSP_EPH_R_R_h.html","rtwtypes_h.html","rtmodel_h.html","MW_target_hardware_resources_h.html"];
