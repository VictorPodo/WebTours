Action()
{

	lr_start_transaction("WebTours");

	web_set_sockets_option("SSL_VERSION", "AUTO");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_url("webtours", 
		"URL=http://192.168.56.1:1080/webtours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("WebTours",LR_AUTO);

	/*Possible OAUTH authorization was detected. It is recommended to correlate the authorization parameters.*/

	lr_start_transaction("SignUp");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	lr_think_time(5);

	web_url("sign up now", 
		"URL=http://192.168.56.1:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://192.168.56.1:1080/WebTours/home.html", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("SignUp",LR_AUTO);

	lr_start_transaction("CustomerProfile");

	web_add_header("Origin", 
		"http://192.168.56.1:1080");

	web_add_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(78);

	web_submit_data("login.pl", 
		"Action=http://192.168.56.1:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer=http://192.168.56.1:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value=Alexey", ENDITEM, 
		"Name=password", "Value=qwerty", ENDITEM, 
		"Name=passwordConfirm", "Value=qwerty", ENDITEM, 
		"Name=firstName", "Value=Alex", ENDITEM, 
		"Name=lastName", "Value=Mason", ENDITEM, 
		"Name=address1", "Value=kirovka 14", ENDITEM, 
		"Name=address2", "Value=Russia, Moscow ", ENDITEM, 
		"Name=register.x", "Value=40", ENDITEM, 
		"Name=register.y", "Value=11", ENDITEM, 
		LAST);

	lr_end_transaction("CustomerProfile",LR_AUTO);

	return 0;
}