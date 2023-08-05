# Database on base of AVL-tree
### Task
Original (in Czech):

"Procestoval jsem takřka celý svět a s klidným svědomím mohu říci, že není národa, který by si Vánoce užíval tolik, jako tito Kdovíci. Co jsem měl možnost se s Kdovíky setkat, poznal jsem, že to není pouhá vidina dárků, radovánek v závějích sněhu a času společně stráveného s rodinou a přáteli. To, co Kdovíci k Vánocům cítí, vychází z hloubi jejich srdce a nebál bych se to nazvat až animózním tužbou či pudovou potřebou šťastných a nerušených Vánoc.

Tedy alespoň u většiny z nich. Tak, jako v každé jiné skupině, se i u Kdovíků najdou výjimky. A nemyslím teď zrovna Grinche. Mám na mysli někoho ještě horšího. Co může být horší, než někdo, kdo z vlastního strachu a z pocitu křivdy chce tomuto nárůdku ukrást Vánoce, ptáte se? No přeci ten, kdo těchto nejnižších lidských pudů využívá, posiluje strach a nejistotu a nabízí na vše jednoduchá řešení. A to všechno s jediným cílem – co nejvíce na tom vydělat. Ano, hádáte dobře, drazí čtenáři. Nejedná se o nikoho jiného než o váženého pana starostu!

U tak naivního národa, jakým Kdovíci jsou, není překvapení, že starosta vládne již několikáté volební období za sebou. Pokaždé se ziskem více než 99 % hlasů. Ty z nás, kteří jsou na světě již nějakou dobu, také nepřekvapí, že ve skutečnosti je pro starostu péče o vesnici pouhý vedlejší zájem. Starosta totiž vlastní to největší (a také jediné, abych byl upřímný) hračkářství v Kdovíkově. Kolosální střet zájmů, řekl by jeden! Našince ovšem nechává chladným.

Dle přísloví „s jídlem roste chuť“ ani starosta nemá dost. V minulém roce proto rozjel akci pracovně nazvanou Nejprodávanější zboží. Tedy masivní digitalizace všech nákupů a analýzu prodejnosti zboží. Na základě obrovského úspěchu, který zdesetinásobil starostovi zisky, hodlá tento rok v digitalizaci pokračovat a dotáhnout ji ještě na vyšší úroveň. Dámy a pánové, přivítejte Nejprodávanější zboží II, ještě zrůdnější akci s cílem vyluxovat řádně peněženky Kdovíků. Zlí jazykové tvrdí, že tato akce nevybere jen úspory, ale možná každému z Kdovíků ukradne i malý kousek duše.

A jak do toho všeho zapadáte Vy? Vždyť Vy jste ti dobří, Vy byste si nešpinili ruce s takovou hanebností. Pravdou ale je, že nikdo jiný, než vedení města a starostovo hračkářství, Vám zakázku nedá. Navíc jste se v minulém roce osvědčili. Proto i tento rok bude implementace Nejprodávanějšího zboží na Vás."

Translation:

"I've traveled almost the entire world, and I can say with a clear conscience that there is no nation that enjoys Christmas as much as the Whoknowsians do. From what I've had the opportunity to experience with the Whoknowsians, I've come to realize that it's not just the vision of gifts, joy in the snowdrifts, and time spent with family and friends. What the Whoknowsians feel for Christmas comes from the depths of their hearts, and I wouldn't hesitate to call it an animistic desire or an instinctual need for happy and undisturbed Christmases.

Well, at least for the majority of them. Just like in any other group, there are exceptions among the Whoknowsians too. And I'm not talking about Grinches now. I mean someone even worse. What could be worse than someone who wants to steal Christmas from this people out of their own fear and a sense of injustice, you ask? Well, the one who exploits these basest human instincts, reinforces fear and uncertainty, and offers simple solutions to everything. And all of this with the sole aim – to profit as much as possible. Yes, dear readers, you guessed it right. I'm talking about none other than the esteemed Mr. Mayor!

In a nation as naive as the Whoknowsians are, it's not surprising that the mayor has been ruling for several election terms in a row. Each time with over 99% of the votes. Those of us who have been in the world for some time are also not surprised that the mayor's actual interest lies elsewhere than taking care of the village. The mayor owns the largest (and only, to be honest) toy store in Whoknows. Colossal conflict of interest, one might say! But it doesn't bother the locals.

According to the proverb 'appetite grows with eating', the mayor's appetite knows no bounds. Therefore, last year he initiated an event workingly named Bestselling Goods. Massive digitization of all purchases and analysis of the merchandise's sales. Based on the tremendous success that multiplied the mayor's profits, he intends to continue with digitization this year and take it to an even higher level. Ladies and gentlemen, welcome the Bestselling Goods II, an even more monstrous event with the goal of thoroughly emptying the wallets of the Whoknowsians. Malignant tongues claim that this event might not only take away savings, but perhaps even snatch a small piece of soul from each Whoknowsian.

And how do you fit into all of this? After all, you're the good ones; you wouldn't dirty your hands with such disgracefulness. But the truth is, no one else but the city's leadership and the mayor's toy store can give you the contract. Besides, you proved yourselves last year. That's why the implementation of the Bestselling Goods falls on you again this year."

### Program Interface

Your task is to implement a template class named Bestsellers parameterized by the type Product, which serves as an identifier for individual products. It is promised that the Product type has a copy constructor (and assignment operator), destructor, comparison operators, and std::hash is implemented for it. The Bestsellers class must implement the following public methods:

size_t products() const - Returns the number of recorded types of products (not the number of sold units).

void sell(const Product& p, size_t amount) - Records the sale of 'amount' units of product 'p'.

size_t rank(const Product& p) const - Returns the rank of the product 'p' among the best-selling products (starting from 1). If multiple products have the same sales count, you can rank them arbitrarily.

const Product& product(size_t rank) const - Inverse function of 'rank'. If no exception occurs, the following holds true: product(rank(p)) == p and rank(product(r)) == r.

size_t sold(size_t r) const - Returns the number of sold units of the product ranked 'r'.

size_t sold(size_t from, size_t to) const - Similar to the single-parameter version, but returns the sum of sold units over the interval from 'from' to 'to' (inclusive on both ends). That is, sold(r, r) == sold(r) and sold(1, products()) is the total number of sold units across all product types. Input where 'to' < 'from' is considered invalid.

Bonus (optional), in src/main.cpp these methods are also implemented:

size_t first_same(size_t r) const - Returns the smallest rank 'r'' for which sold(r') == sold(r).

size_t last_same(size_t r) const - Returns the largest rank 'r'' for which sold(r') == sold(r).
These bonus methods are only used in the bonus test. If you are not tackling the bonus, you can leave the default implementation, which always returns 0.

If the arguments provided in the method calls are invalid (i.e., 'rank' is out of bounds or an unknown product is provided in the 'rank' method), throw an std::out_of_range exception."
