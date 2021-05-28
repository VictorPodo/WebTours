Action()
{
	lr_start_transaction("5_MAIN_RegistrationUser");

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
	

	lr_start_transaction("Click_SignUpNow");

	web_revert_auto_header("Upgrade-Insecure-Requests");
	
	web_reg_find("Text=First time registering? Please complete the form below.", LAST);

	web_url("sign up now", 
		"URL=http://192.168.56.1:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.56.1:1080/WebTours/home.html", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Click_SignUpNow",LR_AUTO);
	
	
	lr_think_time(5);
	
	
	
	lr_start_transaction("FillformRegistration");

	
	web_reg_find("Text=Thank you, <b>{rnd}</b>, for registering and welcome to the Web Tours family.", LAST); 

	web_submit_data("login.pl", 
		"Action=http://192.168.56.1:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer=http://192.168.56.1:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value={rnd}", ENDITEM, 
		"Name=password", "Value={rnd}", ENDITEM, 
		"Name=passwordConfirm", "Value={rnd}", ENDITEM, 
		"Name=firstName", "Value=", ENDITEM, 
		"Name=lastName", "Value=", ENDITEM, 
		"Name=address1", "Value=", ENDITEM, 
		"Name=address2", "Value=", ENDITEM, 
		"Name=register.x", "Value=40", ENDITEM, 
		"Name=register.y", "Value=11", ENDITEM, 
		LAST);

	lr_end_transaction("FillformRegistration",LR_AUTO);
	
	lr_think_time(5);
	
	lr_start_transaction("Continue");
	
	web_reg_find("Text=Welcome, <b>{rnd}</b>, to the Web Tours reservation pages.", LAST);

	web_url("button_next.gif", 
		"URL=http://192.168.56.1:1080/cgi-bin/welcome.pl?page=menus", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.56.1:1080/cgi-bin/login.pl", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Continue",LR_AUTO);
	

	lr_think_time(5);
	
	
	lr_start_transaction("LogOut");

	web_url("SignOff Button", 
		"URL=http://192.168.56.1:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.56.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("LogOut",LR_AUTO);
	
	lr_end_transaction("5_MAIN_RegistrationUser",LR_AUTO);

	return 0;
}