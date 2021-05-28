Action()
{
	lr_start_transaction("4_MAIN_DeletingTickets");
	
	web_reg_save_param_attrib(
		"ParamName=userSession",
		"TagName=input",
		"Extract=value",
		"Name=userSession",
		"Type=hidden",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		"RequestUrl=*/nav.pl*",
		LAST);

	lr_start_transaction("OpenSite");
	
	web_reg_find("Text=Welcome to the Web Tours site.", LAST);

	web_url("webtours", 
		"URL=http://192.168.56.1:1080/webtours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("OpenSite",LR_AUTO);
	
	lr_think_time(5);
	
	lr_start_transaction("Login");
	
	web_reg_find("Text=Welcome, <b>{UserName}</b>, to the Web Tours reservation pages.", LAST);

	web_submit_data("login.pl",
		"Action=http://192.168.56.1:1080/cgi-bin/login.pl",
		"Method=POST",
		"TargetFrame=body",
		"RecContentType=text/html",
		"Referer=http://192.168.56.1:1080/cgi-bin/nav.pl?in=home",
		"Snapshot=t2.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=userSession", "Value={userSession}", ENDITEM,
		"Name=username", "Value={UserName}", ENDITEM,
		"Name=password", "Value={Password}", ENDITEM,
		"Name=login.x", "Value=52", ENDITEM,
		"Name=login.y", "Value=10", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);

	lr_end_transaction("Login",LR_AUTO);
	
	lr_think_time(5);
	
	lr_start_transaction("Click_Itinerary");
	
	web_reg_find("Text=Invoice sent to:", "SaveCount=Tickets_Count", LAST);
	
	web_reg_save_param_attrib(
		"ParamName=flightID",
		"TagName=input",
		"Extract=value",
		"Name=flightID",
		"Type=hidden",
		"NotFound=WARNING",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		"RequestUrl=*/itinerary.pl*",
		LAST);
	
	web_reg_save_param_regexp(
		"ParamName=biletsIDbefore",
		"RegExp=name=\"flightID\"\\ value=\"(.*?)-",
		"Ordinal=all",
		"NotFound=WARNING",
		SEARCH_FILTERS,
		"Scope=Body",
		"IgnoreRedirections=No",
		"RequestUrl=*/itinerary.pl*",
		LAST);
	
	web_url("Itinerary Button", 
		"URL=http://192.168.56.1:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.56.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("Click_Itinerary",LR_AUTO);
	
	lr_think_time(5);
	
	Tickets = atoi(lr_eval_string("{Tickets_Count}"));
	if (Tickets != 0){
			
	lr_start_transaction("Tickets_Remove");
	
	web_reg_save_param_regexp(
		"ParamName=biletsIDafter",
		"RegExp=name=\"flightID\"\\ value=\"(.*?)-",
		"Ordinal=all",
		"NotFound=WARNING",
		SEARCH_FILTERS,
		"Scope=Body",
		"IgnoreRedirections=No",
		"RequestUrl=*/itinerary.pl*",
		LAST);
	
	web_submit_form("itinerary.pl",
		 "Snapshot=t4.inf",
		 ITEMDATA,
		"Name=1", "Value=on", ENDITEM,
		"Name=removeFlights.x", "Value=56", ENDITEM,
		"Name=removeFlights.y", "Value=9", ENDITEM,
	LAST);
	
		ticketsIDbefore_1 = atoi(lr_eval_string("{ticketsIDbefore_1}"));
		ticketsIDafter_1 = atoi(lr_eval_string("{ticketsIDafter_1}"));

if(ticketsIDbefore_1 == ticketsIDafter_1){

	lr_error_message("Error: %s", "the ticket was not deleted");	
	
} else if(ticketsIDbefore_1 != ticketsIDafter_1){

	lr_output_message( "The ticket was deleted #%s", lr_eval_string("{ticketsIDbefore_1}"));

}

	lr_end_transaction("Tickets_Remove",LR_AUTO);
	
	lr_think_time(5);

	lr_start_transaction("Logout");

	web_url("SignOff Button", 
		"URL=http://192.168.56.1:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.56.1:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Logout",LR_AUTO);
	lr_end_transaction("4_MAIN_DeletingTickets",LR_AUTO);
	
	}

else
	
{
	
	web_reg_find("Text=Web Tours", LAST);
	
    lr_start_transaction("Logout");
	web_url("SignOff Button", 
		"URL=http://192.168.26.1:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.26.1:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);
	lr_end_transaction("Logout",LR_AUTO);
	lr_end_transaction("4_MAIN_DeletingTickets",LR_AUTO);
} 

	return 0;
}