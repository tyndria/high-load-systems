How to run server:

1. Be sure that nginx is running: check `http://localhost:8080/` or run ` sudo nginx`
2. See [nginx config](./nginx.conf)

The main part is
```
set $path_info "";  
if ( $fastcgi_script_name ~ ^/hello_world(.*)$ ) {  
	set $path_info $1;  
}  
 	

location /hello_world {
	include fastcgi_params;
	fastcgi_pass unix:/tmp/hello-fcgi-socket;
	fastcgi_param  SCRIPT_NAME        /hello_world;  
	fastcgi_param  PATH_INFO          $path_info;  
}
```

3. See [cppcms config](./hello_world/hello_world/config)
4. Run application with flag `-c config`

