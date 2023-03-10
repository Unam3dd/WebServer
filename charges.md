###  Cahier des Charges

## Serveurs

Il faut pouvoir lancer plusieurs 'serveurs' en un seul fichier de config, par exemple:
	- un serv http qui listen sur 80;
	- un serv https qui listen sur 443;

## Config file

Comme nginx, des blocs `server{}` qui contiennent des directives propres, par exemple:
```
server{
		listen 80;
		addr 127.0.0.1;
		location /{
				redirect https://${addr};
			}
	}
server{
		listen 443;
		addr 127.0.0.1;
		location /{
				document_root /var/www/;
			}
	}
```

## Liste des directives :
	- `listen` : type `t_port`, port sur lequel le server listen;
	- `addr` : type `string`, addr sur laquelle le server listen;
	- `location` : type `t_configblock` 
	- `document` : type `string`, répertoire où aller chercher les fichiers
