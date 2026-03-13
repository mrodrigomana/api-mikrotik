#!/usr/bin/env python3
# brroute.py

from librouteros import connect

# Configurações
HOST = '192.168.0.254'
USER = 'admin'
PASS = 'admin'
PORT = 8728
IP_DESTINO = '192.168.8.1'

try:
    api = connect(host=HOST, username=USER, password=PASS, port=PORT)
    
    # Pega TUDO do cache DNS
    todos = list(api(cmd='/system/identity/print'))
    #"/system/identity/print",
    
    # Filtra manualmente pelo IP
    for registro in todos:
        print(registro)

    todos = list(api(cmd='/ip/firewall/mangle/print'))
    #"/system/identity/print",
    
    # Filtra manualmente pelo IP
    for registro in todos:
        print(registro)

    todos = list(api(cmd='/ip/firewall/mangle/print'))
    #"/system/identity/print",
    
    # Filtra manualmente pelo IP
    for registro in todos:
        print(registro)


except Exception as e:
    print(f"ERRO: {e}")