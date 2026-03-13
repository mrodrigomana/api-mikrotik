# api-mikrotik
This project can be used for get and set commands in a Mikrotik OS that already has the API enabled.



## Fluxo trabalho:

1. Criar uma branch derivada da develop
# Garante que está na develop atualizada
git checkout develop
git pull origin develop

# Cria uma nova branch para sua feature
git checkout -b new-branch

2. Fazer alterações e commits na branch
# Faz as alterações necessárias
git add .
git commit -m "fix1(item1): Ajustes na funcionalidade"

# Mais commits se necessário
git add .
git commit -m "fix2(item2): Ajustes na funcionalidade"

3. Subir a branch para o GitHub
# Primeiro push (cria a branch no remoto)
git push -u origin new-branch

# Próximos pushes (depois do primeiro)
git push

4. Fazer merge para a develop (via Pull Request no GitHub)
FORMA 1: Pelo GitHub (GUI):
Vai até o repositório
Clica em "Compare & pull request" (deve aparecer um banner)
Confere:
Base: develop ← (branch que recebe)
Compare: new-branch ← (sua branch)
Preenche título/descrição
Clica em "Create pull request"
Clica em "Merge pull request" e depois "Confirm merge"

FORMA 2: via GitHub CLI (se tiver instalado):

gh pr create --base develop --head new-branch --title "Título" --body "Descrição"
gh pr merge --merge

5. Atualizar develop local
git checkout develop
git pull origin develop

6. Criar Pull Request da develop para a master
Pelo GitHub:
Vai até o repositório
Clica em "Pull requests" → "New pull request"
Base: master ← (branch protegida)
Compare: develop ← (branch de origem)
Clica em "Create pull request"
Preenche título/descrição
Clica em "Create pull request"

7. Revisar e fazer merge (só você pode aprovar)
Vai na aba "Files changed" para revisar
Clica em "Review changes"
Seleciona "Approve"
Volta à aba "Conversation"
Clica em "Merge pull request" e "Confirm merge"

8. Limpeza (opcional)
# Remove a branch local (depois do merge)
git branch -d new-branch

# Remove a branch remota
git push origin --delete new-branch

9. Sincronizar tudo
# Atualiza master local
git checkout master
git pull origin master

# Atualiza develop local
git checkout develop
git pull origin develop