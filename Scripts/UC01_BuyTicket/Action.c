Action()
{
	
	lr_save_datetime ("%m/%d/%Y", DATE_NOW  + ONE_DAY, "departDate");
	
	lr_save_datetime ("%m/%d/%Y", DATE_NOW	+ ONE_DAY + (ONE_DAY*1), "returnDate");
	
	lr_start_transaction("1_MAIN_BuyTicket");

	lr_start_transaction("OpenSite");
	

	web_set_sockets_option("SSL_VERSION", "AUTO");

/*Correlation comment - Do not change!  Original value='131363.522154719zHfHAVVpVHAiDDDDtAftcpAzHAcf' Name ='userSession' Type ='ResponseBased'*/
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
		"Name=login.x", "Value=68", ENDITEM,
		"Name=login.y", "Value=8", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);


	lr_end_transaction("Login",LR_AUTO);
	
	lr_think_time(5);
	
	lr_start_transaction("Click_Flights");
	
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


	lr_end_transaction("Click_Flights",LR_AUTO);
	
	
	lr_think_time(5);
	
	lr_start_transaction("Fill_Flight");
	
	web_reg_save_param_regexp(
	    "ParamName=outboundFlight", 
	    "RegExp=name=\"outboundFlight\" value=\"([^\"]+)\"",
	    "Ordinal=ALL",
		LAST);
	
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
		"Name=findFlights.x", "Value=55", ENDITEM,
		"Name=findFlights.y", "Value=12", ENDITEM,
		"Name=.cgifields", "Value=roundtrip", ENDITEM,
		"Name=.cgifields", "Value=seatType", ENDITEM,
		"Name=.cgifields", "Value=seatPref", ENDITEM,
		LAST);

	lr_end_transaction("Fill_Flight",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("Choose_Flight");
	
	lr_save_string(lr_paramarr_random("outboundFlight"),"outboundFlight");
	
	
	web_reg_find("Text=Flight Reservation", LAST);

	web_submit_data("reservations.pl_2",
		"Action=http://192.168.56.1:1080/cgi-bin/reservations.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://192.168.56.1:1080/cgi-bin/reservations.pl",
		"Snapshot=t6.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=outboundFlight", "Value={outboundFlight}", ENDITEM,
		"Name=numPassengers", "Value=1", ENDITEM,
		"Name=advanceDiscount", "Value=0", ENDITEM,
		"Name=seatType", "Value={seatType}", ENDITEM,
		"Name=seatPref", "Value={seatPref}", ENDITEM,
		"Name=reserveFlights.x", "Value=41", ENDITEM,
		"Name=reserveFlights.y", "Value=6", ENDITEM,
		LAST);

	lr_end_transaction("Choose_Flight",LR_AUTO);
	
	
	
	lr_think_time(5);
	
	
	
	lr_start_transaction("Fill_Payment_Info");
	
	web_reg_find("Text=<b>{UserName}{LastName}'s Flight Invoice</b>", LAST);

	web_submit_data("reservations.pl_3",
		"Action=http://192.168.56.1:1080/cgi-bin/reservations.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://192.168.56.1:1080/cgi-bin/reservations.pl",
		"Snapshot=t7.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=firstName", "Value={UserName}", ENDITEM,
		"Name=lastName", "Value={LastName}", ENDITEM,
		"Name=address1", "Value={Street}", ENDITEM,
		"Name=address2", "Value={depart}", ENDITEM,
		"Name=pass1", "Value={UserName} {LastName}", ENDITEM,
		"Name=creditCard", "Value={CreditCard}", ENDITEM,
		"Name=expDate", "Value={expDate}", ENDITEM,
		"Name=saveCC", "Value=on", ENDITEM,
		"Name=oldCCOption", "Value=on", ENDITEM,
		"Name=numPassengers", "Value=1", ENDITEM,
		"Name=seatType", "Value={seatType}", ENDITEM,
		"Name=seatPref", "Value={seatPref}", ENDITEM,
		"Name=outboundFlight", "Value={outboundFlight}", ENDITEM,
		"Name=advanceDiscount", "Value=0", ENDITEM,
		"Name=returnFlight", "Value=", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		"Name=buyFlights.x", "Value=40", ENDITEM,
		"Name=buyFlights.y", "Value=10", ENDITEM,
		"Name=.cgifields", "Value=saveCC", ENDITEM,
		LAST);

	lr_end_transaction("Fill_Payment_Info",LR_AUTO);
	
	lr_think_time(5);

	lr_start_transaction("Logout");

	web_url("SignOff Button", 
		"URL=http://192.168.56.1:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.56.1:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Logout",LR_AUTO);
	lr_end_transaction("1_MAIN_BuyTicket",LR_AUTO);

	return 0;
}