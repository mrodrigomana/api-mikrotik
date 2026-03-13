#!/usr/bin/env python3
# brroute.py

from librouteros import connect

def filtrar_registros_firewall(todos_registros, chain=None):
    """
    Filtra e exibe registros do firewall por chain específica
    
    Args:
        todos_registros: Lista com todos os registros do firewall
        chain: String com a chain desejada (forward, input, output, None para todos)
    """
    encontrados = []
    
    for registro in todos_registros:
        if chain is None:  # Se chain for None, mostra todos
            encontrados.append(registro)
            print(registro)
        elif registro.get('chain') == chain:
            encontrados.append(registro)
            print(registro)
    
    if encontrados:
        if chain:
            print(f"\nEncontrados {len(encontrados)} registros na chain {chain}")
            for reg in encontrados:
                print(f"  - Chain: {reg.get('chain')}, Action: {reg.get('action')}, "
                      f"SRC: {reg.get('src-address', 'N/A')}, DST: {reg.get('dst-address', 'N/A')}")
        else:
            print(f"\nTotal de registros encontrados: {len(encontrados)}")
    else:
        print(f"\nNenhum registro encontrado na chain {chain if chain else 'especificada'}")

# Configurações
HOST = '192.168.0.254'
USER = 'admin'
PASS = 'admin'
PORT = 8728
IP_DESTINO = '192.168.8.1'

try:
    api = connect(host=HOST, username=USER, password=PASS, port=PORT)
    
    # Pega TUDO do cache DNS
    todos = list(api(cmd='/ip/dns/cache/all/print'))
    
    # Filtra manualmente pelo IP
    encontrado = None
    for registro in todos:
        if registro.get('data') == IP_DESTINO:
            encontrado = registro
            print(registro)
            break
    
    if encontrado:
        print(f"{encontrado['name']} {encontrado['data']}")
    else:
        print("Não encontrado")

    # Pega todos os registros do firewall
    todos_firewall = list(api(cmd='/ip/firewall/filter/print'))
    
    print("\n" + "="*50)
    print("FILTRANDO FIREWALL:")
    print("="*50)
    
    # Exemplos de uso da função
    print("\n--- Mostrando apenas FORWARD ---")
    filtrar_registros_firewall(todos_firewall, 'forward')
    
    print("\n--- Mostrando apenas INPUT ---")
    filtrar_registros_firewall(todos_firewall, 'input')
    
    print("\n--- Mostrando apenas OUTPUT ---")
    filtrar_registros_firewall(todos_firewall, 'output')
    
    print("\n--- Mostrando TODOS os registros ---")
    filtrar_registros_firewall(todos_firewall)  # chain=None mostra todos


    todos_firewall = list(api(cmd='/ip/firewall/nat/print'))

    print("\n" + "="*50)
    print("FILTRANDO NAT:")
    print("="*50)
    
    # Exemplos de uso da função
    print("\n--- Mostrando apenas FORWARD ---")
    filtrar_registros_firewall(todos_firewall, 'srcnat')
        
except Exception as e:
    print(f"ERRO: {e}")