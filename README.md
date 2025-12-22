# baba-is-you

# TO-DO 

## Nécessaire pour la soutenance
- Faire en sorte que make lance directement le programme, qu'on ai pas besoin de faire ./prog
- Affichage des TEXT_FLAG et des TEXT_WIN
- Gagner le jeu (prise en charge des trucs IS WIN)
- Perdre le jeu (eau, TRUC IS DEAD)
- Prise en charge de la taille de la fenêtre (la fenêtre doit prendre tout l'écran, avec des bandes noires en dehors de la grille)
- faire des includes propres (pas besoin de vector et set partout, parfois on include des trucs dont on a pas besoin ...)
- (important) clarifier le model, vue, controlleur. je pense que ces trois doivent avoir plus d'indépendance entre eux, or là on dirait un peu que tout le monde à accès à tout le monde ... (i.e friend)

## Détails importants
- à chaque fois qu'on fait un switch, il faut faire une sécurité dans le cas où le switch correspond à rien, genre un throw erreur. notamment, dans model.cpp (ObjetToRuleSubject, TextPropertyToRuleProperty, TextObjectToRuleSubject) et dans board elements (intToBoardElementType)
- même chose pour board load_level : il faut prendre en compte le cas où le fichier serait corrompu / mal formé. 
- plutôt faiere subject < other.subject || (subject == other.subject && property < other.property) pour rulekey::operator<
- quand on fera le loader de niveau, faire attention à la gestion de la mémoire, notamment void Board::createEmptyGrid(int width, int height) (dans board.cpp) qui crée directement une nouvelle grille sans check que on a pas détruit l'ancienne
- il manque la rule of three chez board, view, etc ... par exemple, on devrait pas pouvoir construire un board par copie donc Board(const Board&) = delete;, ni pouvoir (ou peut être qu'on voudra ?) comparer deux boards Board& operator=(const Board&) = delete;
Même chose, les constructeurs par défauts doivent être delete quand ils doivent pas exister.
- problème de sécurité d'accès : 
(je pense qu'on peut rester assez laxistes, genre par exemple getPosition pour BoardElement on peut le laisser public, même si en vrai pas tout le monde devrait pouvoir y avoir accès.)

#### Board
- loadLevel et setNewPosition doit pas être pbc
- même chose pour createEmptyGrid
- a priori, on pourrait se dire que le constructeur devrait pas être public vu que seul le Model devrait pouvoir créer un board ... a voir.
- la View et le Model ont vraiment besoin d'être friend ? Le Model ok c'est sur, mais la View je me dis vu qu'elle peut avoir accès à n'importe quel element avec getCell ... Je pense que la View devrait pas être friend. 

#### BoardElement
- setPostionX/Y doivent pas être public
- intToBoardElementType peut être pas nn plus

#### Controller
- handleEvent devrait être privé modulo le main qui a accès (a voir en fonction de comment on implémente la gestion des niveaux)

#### Model
- pareil, la view a-t-elle vraiment besoin d'être friend ? 
- redéfinir / delete le constructeur par défaut / copie et la surchage de = 
- le constrcteur devrait aps être public vu que seul le main peut créer un model.
- pareil pour move seul le controleur devrait pouvoir appeler
- pas clair sur la gestion du  Board board et du Rules rules dans les attributs : ils sont initialisés quand ? comment ? 


#### Rules
- je comprends pas la différence rulekey et rules
- clearrules et setrule devraient pas être publics