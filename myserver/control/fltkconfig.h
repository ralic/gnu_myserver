// generated by Fast Light User Interface Designer (fluid) version 1.0108

#ifndef fltkconfig_h
#define fltkconfig_h
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Progress.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Counter.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/fl_ask.H>
#include "../include/xml_parser.h"
#include "../include/stringutils.h"
#include "../include/md5.h"
#include "../include/utility.h"
#include "service.h"
#include "language.h"
#include "mimetype.h"
#include "vhost.h"
#include "control_client.h"
#include "progress.h"

class MainDlg {
public:
  Fl_Double_Window* make_window();
  Fl_Double_Window *ConfDlg;
private:
  void cb_ConfDlg_i(Fl_Double_Window*, void*);
  static void cb_ConfDlg(Fl_Double_Window*, void*);
  static Fl_Menu_Item menu_[];
  void cb_Open_i(Fl_Menu_*, void*);
  static void cb_Open(Fl_Menu_*, void*);
  void cb_Save_i(Fl_Menu_*, void*);
  static void cb_Save(Fl_Menu_*, void*);
  void cb_Revert_i(Fl_Menu_*, void*);
  static void cb_Revert(Fl_Menu_*, void*);
  void cb_as_i(Fl_Menu_*, void*);
  static void cb_as(Fl_Menu_*, void*);
  void cb_as1_i(Fl_Menu_*, void*);
  static void cb_as1(Fl_Menu_*, void*);
  void cb_Console_i(Fl_Menu_*, void*);
  static void cb_Console(Fl_Menu_*, void*);
  void cb_Service_i(Fl_Menu_*, void*);
  static void cb_Service(Fl_Menu_*, void*);
  void cb_Quit_i(Fl_Menu_*, void*);
  static void cb_Quit(Fl_Menu_*, void*);
  void cb_Install_i(Fl_Menu_*, void*);
  static void cb_Install(Fl_Menu_*, void*);
  void cb_Remove_i(Fl_Menu_*, void*);
  static void cb_Remove(Fl_Menu_*, void*);
  void cb_Login_i(Fl_Menu_*, void*);
  static void cb_Login(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *MenuLogout;
private:
  void cb_MenuLogout_i(Fl_Menu_*, void*);
  static void cb_MenuLogout(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *MenuGetConfig;
private:
  void cb_MenuGetConfig_i(Fl_Menu_*, void*);
  static void cb_MenuGetConfig(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *MenuSendConfig;
private:
  void cb_MenuSendConfig_i(Fl_Menu_*, void*);
  static void cb_MenuSendConfig(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *MenuConnections;
private:
  void cb_MenuConnections_i(Fl_Menu_*, void*);
  static void cb_MenuConnections(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *MenuReboot;
private:
  void cb_MenuReboot_i(Fl_Menu_*, void*);
  static void cb_MenuReboot(Fl_Menu_*, void*);
  void cb_About_i(Fl_Menu_*, void*);
  static void cb_About(Fl_Menu_*, void*);
public:
  Fl_Value_Input *Buffer_Size;
private:
  void cb_Buffer_Size_i(Fl_Value_Input*, void*);
  static void cb_Buffer_Size(Fl_Value_Input*, void*);
public:
  Fl_Choice *Verbosity;
private:
  void cb_Verbosity_i(Fl_Choice*, void*);
  static void cb_Verbosity(Fl_Choice*, void*);
  static Fl_Menu_Item menu_Verbosity[];
public:
  Fl_Value_Input *Max_Log_File_Size;
private:
  void cb_Max_Log_File_Size_i(Fl_Value_Input*, void*);
  static void cb_Max_Log_File_Size(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *Nthreads_Static;
private:
  void cb_Nthreads_Static_i(Fl_Value_Input*, void*);
  static void cb_Nthreads_Static(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *Nthreads_Max;
private:
  void cb_Nthreads_Max_i(Fl_Value_Input*, void*);
  static void cb_Nthreads_Max(Fl_Value_Input*, void*);
public:
  Fl_Choice *Language;
private:
  void cb_Language_i(Fl_Choice*, void*);
  static void cb_Language(Fl_Choice*, void*);
public:
  Fl_Value_Input *Connection_Timeout;
private:
  void cb_Connection_Timeout_i(Fl_Value_Input*, void*);
  static void cb_Connection_Timeout(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *Max_Connections;
private:
  void cb_Max_Connections_i(Fl_Value_Input*, void*);
  static void cb_Max_Connections(Fl_Value_Input*, void*);
public:
  Fl_Value_Input *Gzip_Threshold;
private:
  void cb_Gzip_Threshold_i(Fl_Value_Input*, void*);
  static void cb_Gzip_Threshold(Fl_Value_Input*, void*);
public:
  Fl_Input *Browsefolder_Css;
private:
  void cb_Browsefolder_Css_i(Fl_Input*, void*);
  static void cb_Browsefolder_Css(Fl_Input*, void*);
  void cb_Browse_i(Fl_Button*, void*);
  static void cb_Browse(Fl_Button*, void*);
public:
  Fl_Check_Button *Use_Errors_Files;
private:
  void cb_Use_Errors_Files_i(Fl_Check_Button*, void*);
  static void cb_Use_Errors_Files(Fl_Check_Button*, void*);
public:
  Fl_Browser *Default_Filename;
private:
  void cb_Add_i(Fl_Button*, void*);
  static void cb_Add(Fl_Button*, void*);
  void cb_Remove1_i(Fl_Button*, void*);
  static void cb_Remove1(Fl_Button*, void*);
public:
  Fl_Browser *Ext;
private:
  void cb_Ext_i(Fl_Browser*, void*);
  static void cb_Ext(Fl_Browser*, void*);
  void cb_Add1_i(Fl_Button*, void*);
  static void cb_Add1(Fl_Button*, void*);
  void cb_Remove2_i(Fl_Button*, void*);
  static void cb_Remove2(Fl_Button*, void*);
public:
  Fl_Choice *Mime;
private:
  void cb_Mime_i(Fl_Choice*, void*);
  static void cb_Mime(Fl_Choice*, void*);
  void cb_Add2_i(Fl_Button*, void*);
  static void cb_Add2(Fl_Button*, void*);
public:
  Fl_Choice *Cmd;
private:
  void cb_Cmd_i(Fl_Choice*, void*);
  static void cb_Cmd(Fl_Choice*, void*);
  static Fl_Menu_Item menu_Cmd[];
public:
  Fl_Input *Manager;
private:
  void cb_Manager_i(Fl_Input*, void*);
  static void cb_Manager(Fl_Input*, void*);
public:
  Fl_Button *ManagerButton;
private:
  void cb_ManagerButton_i(Fl_Button*, void*);
  static void cb_ManagerButton(Fl_Button*, void*);
public:
  Fl_Choice *Name;
private:
  void cb_Name_i(Fl_Choice*, void*);
  static void cb_Name(Fl_Choice*, void*);
  void cb_Add3_i(Fl_Button*, void*);
  static void cb_Add3(Fl_Button*, void*);
  void cb_Remove3_i(Fl_Button*, void*);
  static void cb_Remove3(Fl_Button*, void*);
public:
  Fl_Choice *Protocol;
private:
  void cb_Protocol_i(Fl_Choice*, void*);
  static void cb_Protocol(Fl_Choice*, void*);
  static Fl_Menu_Item menu_Protocol[];
public:
  Fl_Input *Ssl_Privatekey;
private:
  void cb_Ssl_Privatekey_i(Fl_Input*, void*);
  static void cb_Ssl_Privatekey(Fl_Input*, void*);
public:
  Fl_Input *Ssl_Certificate;
private:
  void cb_Ssl_Certificate_i(Fl_Input*, void*);
  static void cb_Ssl_Certificate(Fl_Input*, void*);
public:
  Fl_Input *Ssl_Password;
private:
  void cb_Ssl_Password_i(Fl_Input*, void*);
  static void cb_Ssl_Password(Fl_Input*, void*);
public:
  Fl_Button *SslButton1;
private:
  void cb_SslButton1_i(Fl_Button*, void*);
  static void cb_SslButton1(Fl_Button*, void*);
public:
  Fl_Button *SslButton2;
private:
  void cb_SslButton2_i(Fl_Button*, void*);
  static void cb_SslButton2(Fl_Button*, void*);
public:
  Fl_Browser *Host;
  Fl_Browser *Ip;
private:
  void cb_Add4_i(Fl_Button*, void*);
  static void cb_Add4(Fl_Button*, void*);
  void cb_Remove4_i(Fl_Button*, void*);
  static void cb_Remove4(Fl_Button*, void*);
  void cb_Add5_i(Fl_Button*, void*);
  static void cb_Add5(Fl_Button*, void*);
  void cb_Remove5_i(Fl_Button*, void*);
  static void cb_Remove5(Fl_Button*, void*);
public:
  Fl_Value_Input *Port;
private:
  void cb_Port_i(Fl_Value_Input*, void*);
  static void cb_Port(Fl_Value_Input*, void*);
public:
  Fl_Check_Button *Allow_CGI;
private:
  void cb_Allow_CGI_i(Fl_Check_Button*, void*);
  static void cb_Allow_CGI(Fl_Check_Button*, void*);
public:
  Fl_Check_Button *Allow_ISAPI;
private:
  void cb_Allow_ISAPI_i(Fl_Check_Button*, void*);
  static void cb_Allow_ISAPI(Fl_Check_Button*, void*);
public:
  Fl_Check_Button *Allow_MSCGI;
private:
  void cb_Allow_MSCGI_i(Fl_Check_Button*, void*);
  static void cb_Allow_MSCGI(Fl_Check_Button*, void*);
public:
  Fl_Check_Button *Allow_WINCGI;
private:
  void cb_Allow_WINCGI_i(Fl_Check_Button*, void*);
  static void cb_Allow_WINCGI(Fl_Check_Button*, void*);
public:
  Fl_Check_Button *Allow_FASTCGI;
private:
  void cb_Allow_FASTCGI_i(Fl_Check_Button*, void*);
  static void cb_Allow_FASTCGI(Fl_Check_Button*, void*);
public:
  Fl_Check_Button *Allow_SCGI;
private:
  void cb_Allow_SCGI_i(Fl_Check_Button*, void*);
  static void cb_Allow_SCGI(Fl_Check_Button*, void*);
public:
  Fl_Check_Button *Allow_SEND_LINK;
private:
  void cb_Allow_SEND_LINK_i(Fl_Check_Button*, void*);
  static void cb_Allow_SEND_LINK(Fl_Check_Button*, void*);
public:
  Fl_Check_Button *Allow_EXTERNAL_COMMANDS;
private:
  void cb_Allow_EXTERNAL_COMMANDS_i(Fl_Check_Button*, void*);
  static void cb_Allow_EXTERNAL_COMMANDS(Fl_Check_Button*, void*);
public:
  Fl_Check_Button *Allow_SEND_FILE;
private:
  void cb_Allow_SEND_FILE_i(Fl_Check_Button*, void*);
  static void cb_Allow_SEND_FILE(Fl_Check_Button*, void*);
public:
  Fl_Input *Docroot;
private:
  void cb_Docroot_i(Fl_Input*, void*);
  static void cb_Docroot(Fl_Input*, void*);
public:
  Fl_Input *Sysfolder;
private:
  void cb_Sysfolder_i(Fl_Input*, void*);
  static void cb_Sysfolder(Fl_Input*, void*);
  void cb_Browse1_i(Fl_Button*, void*);
  static void cb_Browse1(Fl_Button*, void*);
  void cb_Browse2_i(Fl_Button*, void*);
  static void cb_Browse2(Fl_Button*, void*);
public:
  Fl_Input *Accesseslog;
private:
  void cb_Accesseslog_i(Fl_Input*, void*);
  static void cb_Accesseslog(Fl_Input*, void*);
public:
  Fl_Input *Warninglog;
private:
  void cb_Warninglog_i(Fl_Input*, void*);
  static void cb_Warninglog(Fl_Input*, void*);
public:
  Fl_Input *Server_Admin;
private:
  void cb_Server_Admin_i(Fl_Input*, void*);
  static void cb_Server_Admin(Fl_Input*, void*);
public:
  Fl_Input *Control_Admin;
private:
  void cb_Control_Admin_i(Fl_Input*, void*);
  static void cb_Control_Admin(Fl_Input*, void*);
public:
  Fl_Input *Control_Password;
private:
  void cb_Control_Password_i(Fl_Input*, void*);
  static void cb_Control_Password(Fl_Input*, void*);
public:
  Fl_Check_Button *Control_Enabled;
private:
  void cb_Control_Enabled_i(Fl_Check_Button*, void*);
  static void cb_Control_Enabled(Fl_Check_Button*, void*);
public:
  Fl_Check_Button *Allow_Anonymous;
private:
  void cb_Allow_Anonymous_i(Fl_Check_Button*, void*);
  static void cb_Allow_Anonymous(Fl_Check_Button*, void*);
public:
  Fl_Check_Button *Anonymous_Needs_Password;
private:
  void cb_Anonymous_Needs_Password_i(Fl_Check_Button*, void*);
  static void cb_Anonymous_Needs_Password(Fl_Check_Button*, void*);
public:
  Fl_Check_Button *Allow_Asynchronous_Cmds;
private:
  void cb_Allow_Asynchronous_Cmds_i(Fl_Check_Button*, void*);
  static void cb_Allow_Asynchronous_Cmds(Fl_Check_Button*, void*);
public:
  Fl_Check_Button *Allow_Pipelining;
private:
  void cb_Allow_Pipelining_i(Fl_Check_Button*, void*);
  static void cb_Allow_Pipelining(Fl_Check_Button*, void*);
public:
  Fl_Check_Button *Allow_Store_Cmds;
private:
  void cb_Allow_Store_Cmds_i(Fl_Check_Button*, void*);
  static void cb_Allow_Store_Cmds(Fl_Check_Button*, void*);
public:
  Fl_Double_Window* make_type();
  Fl_Double_Window *ConfTypeDlg;
  Fl_Round_Button *ConfTypeDlgLocal;
private:
  void cb_ConfTypeDlgLocal_i(Fl_Round_Button*, void*);
  static void cb_ConfTypeDlgLocal(Fl_Round_Button*, void*);
public:
  Fl_Round_Button *ConfTypeDlgUser;
private:
  void cb_ConfTypeDlgUser_i(Fl_Round_Button*, void*);
  static void cb_ConfTypeDlgUser(Fl_Round_Button*, void*);
public:
  Fl_Round_Button *ConfTypeDlgGlobal;
private:
  void cb_ConfTypeDlgGlobal_i(Fl_Round_Button*, void*);
  static void cb_ConfTypeDlgGlobal(Fl_Round_Button*, void*);
public:
  Fl_Return_Button *ConfTypeDlgOK;
  Fl_Button *ConfTypeDlgCancel;
  Fl_Double_Window* make_about();
  Fl_Double_Window *AboutDlg;
  Fl_Text_Display *AboutText;
private:
  void cb_OK_i(Fl_Return_Button*, void*);
  static void cb_OK(Fl_Return_Button*, void*);
public:
  Fl_Double_Window* make_login();
  Fl_Double_Window *LoginDlg;
  Fl_Input *LoginDlgAddress;
  Fl_Value_Input *LoginDlgPort;
  Fl_Input *LoginDlgName;
  Fl_Input *LoginDlgPass;
  Fl_Return_Button *LoginDlgOK;
  Fl_Button *LoginDlgCancel;
  Fl_Double_Window* make_status();
  Fl_Double_Window *StatusDlg;
  Fl_Group *StatusDlgGroup;
  Fl_Progress *StatusDlgProgress;
  Fl_Double_Window* make_connections();
  Fl_Double_Window *ConnectionsDlg;
  Fl_Output *ConnectionsDlgVr;
  Fl_Browser *ConnectionsDlgList;
  Fl_Counter *ConnectionsDlgRate;
  Fl_Button *ConnectionsDlgKill;
  Fl_Button *ConnectionsDlgDone;
  Fl_Double_Window* make_regask();
  Fl_Double_Window *RegaskDlg;
  Fl_Input *RegaskDlgInput;
  Fl_Button *RegaskDlgCancel;
  Fl_Return_Button *RegaskDlgOK;
  Fl_Check_Button *RegaskDlgRegex;
  int ask_type();
  int load_config();
  int load_config_remote();
  int load_myserver_core();
  int save_config();
  int save_config_remote();
  int save_myserver_core();
  void setDynamic(Vector & list);
  int ConfType; 
private:
  const char * getValueXML(const char * name);
  void setValueXML(const char * name, const char * value);
  void ServerLogout();
  int ServerLogin(bool stat);
  void ServerConnections();
  char * regex_input(const char * capt, bool & reg);
  void fl_alertcat(const char * c1, const char * c2);
  void fl_wait(int len);
  const char * mystrcat(const char * a, const char * b);
  bool Changed; 
  MIMEtypeXML MimeConf; 
  VHostXML VHostConf; 
  XmlParser xmlFile; 
  ControlClient Server; 
};
#endif
