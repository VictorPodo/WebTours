Action()
{
	
	lr_save_datetime ("%m/%d/%Y", DATE_NOW  + ONE_DAY, "departDate");
	
	lr_save_datetime ("%m/%d/%Y", DATE_NOW	+ ONE_DAY + (ONE_DAY*1), "returnDate");
	
	lr_start_transaction("3_MAIN_TicketSearch");
	
	lr_start_transaction("OpenSite");

	web_set_sockets_option("SSL_VERSION", "AUTO");

/*Correlation comment - Do not change!  Original value='131364.50927501zHfHAzVpQtfiDDDDtAftcpDHVzHf' Name ='userSession' Type ='ResponseBased'*/
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

	/*Possible OAUTH authorization was detected. It is recommended to correlate the authorization parameters.*/

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
		"Name=login.x", "Value=0", ENDITEM,
		"Name=login.y", "Value=0", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);


	web_submit_data("login.pl",
		"Action=http://192.168.56.1:1080/cgi-bin/login.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://192.168.56.1:1080/cgi-bin/nav.pl?in=home",
		"Snapshot=t3.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=userSession", "Value={userSession}", ENDITEM,
		"Name=username", "Value={UserName}", ENDITEM,
		"Name=password", "Value={Password}", ENDITEM,
		"Name=login.x", "Value=55", ENDITEM,
		"Name=login.y", "Value=8", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);

	lr_end_transaction("Login",LR_AUTO);
	
	lr_think_time(5);

	lr_start_transaction("ClickFlights");

	web_reg_save_param_ex(
		"ParamName=town", 
	    "LB/IC=<option value=\"",
	    "RB/IC=\">",
	    "Ordinal=all",
		LAST);
		
	web_reg_find("Text=Web Tours Navigation Bar", LAST);

	web_url("Search Flights Button", 
		"URL=http://192.168.56.1:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.56.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_save_string(lr_paramarr_random("town"), "depart");
	lr_save_string(lr_paramarr_random("town"), "arrive");
	
	while(strcmp(lr_eval_string("{depart}"), lr_eval_string("{arrive}"))== 0){
		lr_save_string(lr_paramarr_random("town"), "arrive");
	}


	lr_end_transaction("ClickFlights",LR_AUTO);
	
	lr_think_time(5);

	lr_start_transaction("FillFlight");
	
	
	web_reg_find("Text=Flight departing from <B>{depart}</B> to <B>{arrive}</B> on <B>{departDate}</B>", LAST);

	web_submit_data("reservations.pl",
		"Action=http://192.168.56.1:1080/cgi-bin/reservations.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://192.168.56.1:1080/cgi-bin/reservations.pl?page=welcome",
		"Snapshot=t5.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=advanceDiscount", "Value=0", ENDITEM,
		"Name=depart", "Value={depart}", ENDITEM,
		"Name=departDate", "Value={departDate}", ENDITEM,
		"Name=arrive", "Value={arrive}", ENDITEM,
		"Name=returnDate", "Value={returnDate}", ENDITEM,
		"Name=numPassengers", "Value=1", ENDITEM,
		"Name=seatPref", "Value={seatPref}", ENDITEM,
		"Name=seatType", "Value={seatType}", ENDITEM,
		"Name=findFlights.x", "Value=41", ENDITEM,
		"Name=findFlights.y", "Value=9", ENDITEM,
		"Name=.cgifields", "Value=roundtrip", ENDITEM,
		"Name=.cgifields", "Value=seatType", ENDITEM,
		"Name=.cgifields", "Value=seatPref", ENDITEM,
		LAST);

	lr_end_transaction("FillFlight",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("LogOut");

	web_url("SignOff Button", 
		"URL=http://192.168.56.1:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.56.1:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("LogOut",LR_AUTO);
	lr_end_transaction("3_MAIN_TicketSearch",LR_AUTO);

	return 0;
}