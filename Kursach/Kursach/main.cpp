#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <list>
using namespace sf;

//
//глобальні змінні
int ts = 54; //tile size
std::list<int> l1;
std::string fileres = "hello.txt";
int gameTime = 0;
Vector2i offset(48, 24);
bool isMenu = true;
//bool isMn = 1;
bool status = true;


void ReadFromFile(){
	std::string line;
	std::ifstream f1(fileres);
	l1.clear();
	//файл існує
	if (f1.is_open()){
		while (getline(f1, line))
		{
			l1.push_back(atoi(line.c_str()));
		}
		f1.close();
		//приведемо список в потрібний нам вид
		l1.sort();
		l1.reverse();
		if (l1.size() > 8) {
			l1.resize(8);
		}
	}
	//файл відсутній - створимо його
	else {
		std::ofstream f1(fileres, std::ios::trunc);
		if (f1.is_open()) {
			f1.close();
		}
	}
}

void WriteToFile(){
	std::ofstream f1(fileres, std::ios::trunc | std::ios::beg);
	if (f1.is_open()){
		for (auto v1 : l1){
			f1 << v1 << std::endl;
		}
		f1.close();
	}

}

//
////int och = 0;
//int gameTime = 0;
//Vector2i offset(48, 24);
//bool isMenu = true;
////bool isMn = 1;
//bool status = true;
struct piece
{
	int x, y, col, row, kind, match, alpha;
	piece(){ match = 0; alpha = 255; }
} grid[10][10];

void swap(piece p1, piece p2)
{
	std::swap(p1.col, p2.col);
	std::swap(p1.row, p2.row);

	grid[p1.row][p1.col] = p1;
	grid[p2.row][p2.col] = p2;
}
//////////////////////////////////////////////////


//////////////////////////////////////////////////
bool menu(RenderWindow & window) {
	int b = 0;
	Font font;//шрифт 
	font.loadFromFile("CyrillicOld.ttf");//передаем нашему шрифту файл шрифта
	Text text5("", font, 50);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text5.setFillColor(Color::Red);

	Text tt("", font, 50);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	//text.setOutlineColor(Color::Blue);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	tt.setFillColor(Color::Red);
	tt.setStyle(Text::Bold);//жир

	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images/1111.png");
	menuTexture2.loadFromFile("images/222.png");
	menuTexture3.loadFromFile("images/333.png");
	aboutTexture.loadFromFile("images/about.png");
	menuBackground.loadFromFile("images/about.png");

	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = true;
	int menuNum = 0;

	menu1.setPosition(740 / 2 - menu1.getLocalBounds().width / 2, 480 / 2 - menu1.getLocalBounds().height / 0.5);
	menu2.setPosition(740 / 2 - menu2.getLocalBounds().width / 2, 480 / 1.7f - menu2.getLocalBounds().height / 0.6);
	menu3.setPosition(740 / 2 - menu3.getLocalBounds().width / 2, 480 / 1.4f - menu3.getLocalBounds().height / 0.45);
	menuBg.setPosition(0, 0);
	//about.setPosition(0, 0);
	//////////////////////////////МЕНЮ///////////////////
	float anti=0;
	while (isMenu)
	{
		Clock clock;
		float time = clock.getElapsedTime().asMicroseconds();
		time /= 800;
		anti += time;
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed)  { window.close(); isMenu = false; }
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));
		
		if (IntRect(menu1.getPosition().x, menu1.getPosition().y, menu1.getLocalBounds().width, menu1.getLocalBounds().height).contains(Mouse::getPosition(window))&& anti>0.006f) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(menu2.getPosition().x, menu2.getPosition().y, menu2.getLocalBounds().width, menu2.getLocalBounds().height).contains(Mouse::getPosition(window)) && anti>0.006f) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(menu3.getPosition().x, menu3.getPosition().y, menu3.getLocalBounds().width, menu3.getLocalBounds().height).contains(Mouse::getPosition(window)) && anti>0.006f) { menu3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) { isMenu = false;  return true; }//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) {
				window.draw(about);
				window.display();

				std::string line;
				ReadFromFile();
				std::ifstream in("hello.txt"); // окрываем файл для чтения
				if (in.is_open())
				{
					int  y = 0;
					while (getline(in, line))
					{
						y += 50; 
						b++;
						//std::cout << line << std::endl;
						text5.setString(line);
						text5.setPosition(740 / 2 - text5.getLocalBounds().width / 1.5,y / 1 - text5.getLocalBounds().height / 2.5);
						
						std::string bb = std::to_string(b);
						tt.setString(bb+".");	//задаем строку тексту и вызываем сформированную выше строку методом .str() 
						tt.setPosition(280, y / 1 - tt.getLocalBounds().height / 2.5);
						
						window.draw(text5);
						window.draw(tt);
						window.display();

					}
				}
				in.close();     // закрываем файл

				while (!Keyboard::isKeyPressed(Keyboard::Escape));
			}
			if (menuNum == 3)  { isMenu = false; return false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
	////////////////////////////////////////////////////
	return true;
}

void Input(RenderWindow & window){

	Font font;//шрифт 
	font.loadFromFile("CyrillicOld.ttf");//передаем нашему шрифту файл шрифта
	Text text4("", font, 40);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	//text.setOutlineColor(Color::Blue);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text4.setFillColor(Color::Blue);
	text4.setStyle(Text::Bold | Text::Underlined);
	bool startGame();
	Texture t, m, back; // создаём текстуру главного персонажа
	t.loadFromFile("images/dopmen.jpg"); //загружаем картинку из файла
	m.loadFromFile("images/1111.png");
	back.loadFromFile("images/111.png");
	Sprite s, b, men; // создаём спрайт главного персонажа
	men.setTexture(back);
	s.setTexture(t); // "заряжаем" спрайт текстурой
	b.setTexture(m);
	men.setPosition(740 / 2 - men.getLocalBounds().width / 2,480 / 2.5f - men.getLocalBounds().height / 2);

	b.setPosition(740 / 2 - b.getLocalBounds().width / 2, 480 / 2 - s.getLocalBounds().height / 20);

	s.setPosition(740 / 2 - s.getLocalBounds().width / 2, 480 / 2 - s.getLocalBounds().height / 1.9);
	bool isMn = true;
	int menuNum = 0;
	std::string ss;
	while (isMn)
	{

		b.setColor(Color::White);
		men.setColor(Color::White);
		int menuNum = 0;

		//app.clear(Color(129, 181, 221));
		if (IntRect(men.getPosition().x, men.getPosition().y, men.getLocalBounds().width, men.getLocalBounds().height).contains(Mouse::getPosition(window))) { men.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(b.getPosition().x, b.getPosition().y, b.getLocalBounds().width, b.getLocalBounds().height).contains(Mouse::getPosition(window))) { b.setColor(Color::Blue); menuNum = 1; }
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) {
				status = false;
				isMn = false;
			}
			if (menuNum == 2){
				isMn = false;
				status = true;
			}

		}
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == Event::Closed)  window.close();
		}


		window.draw(s);
		window.draw(men);
		window.draw(b);
		window.draw(text4);

		window.display();
	}
	
	
}

///////////////////////////////////////////////////
bool startGame(RenderWindow & window){
	if (status && menu(window)){}
	else if (!status){}
	else return false;
	Event e;
	std::string ss;

	srand(time(0));
	int och = 0;



	Font font;//шрифт 
	font.loadFromFile("CyrillicOld.ttf");//передаем нашему шрифту файл шрифта

	

	Text text("", font, 30);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	//text.setOutlineColor(Color::Blue);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text.setFillColor(Color::Blue);
	text.setStyle(Text::Bold | Text::Underlined);//жир
	Text text1("", font, 30);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	//text.setOutlineColor(Color::Blue);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text1.setFillColor(Color::Blue);
	text1.setStyle(Text::Bold | Text::Underlined);//жир
	/////////////
	
	///
	Text text3("", font, 30);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	//text.setOutlineColor(Color::Blue);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text3.setFillColor(Color::Blue);
	text3.setStyle(Text::Bold | Text::Underlined);//жир
	///////////
	Text text4("", font, 40);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	//text.setOutlineColor(Color::Blue);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text4.setFillColor(Color::Blue);
	text4.setStyle(Text::Bold | Text::Underlined);//жир
	/////
	Texture t1, t2;
	t1.loadFromFile("images/background.png");
	t2.loadFromFile("images/gems.png");

	Sprite background(t1), gems(t2);

	for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++)
		{
			grid[i][j].kind = rand() % 5;
			grid[i][j].col = j;
			grid[i][j].row = i;
			grid[i][j].x = j*ts;
			grid[i][j].y = i*ts;
		}

	int x0 = 0, y0 = 0, x, y; int click = 0; Vector2i pos;
	bool isSwap = false, isMoving = false;
	Clock clock;
	Clock gameTimeClock;
	////



	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asSeconds(); //дать прошедшее время в микросекундах
		//gameTime =gameTimeClock.getElapsedTime().asSeconds();//игровое время в секундах идёт вперед, пока жив игрок, перезагружать как time его не надо. оно не обновляет логику игры
		if (gameTime < 21){
			gameTime = gameTimeClock.getElapsedTime().asSeconds();
			std::cout << "vada";
			clock.restart();
			time = time / 800;
			// menu(window);//вызов меню
		}

		int t = 0;
		//если эскейп, то выходим из игры
		if (Keyboard::isKeyPressed(Keyboard::Escape)) gameTime = 21;
		if (gameTime > 20){
			//зчитати результати поточні
			ReadFromFile();
			//добавив останній результата в список
			l1.push_back(och);
			//відсортував список по збільшеннюю
			l1.sort();
			//перевернув список - від більшого до меншого
			l1.reverse();
			//видалив зі списку одинакові результати
			l1.unique();
			//якщо список більше 10 результатів - обрізати лишні знизу
			
			if (l1.size() > 8){
				l1.resize(8);
			}
			//зберегти список в файл
			WriteToFile();
			Input(window); 
		
			gameTime = 0;
			return true;
	


		}
		std::cout << gameTime;

		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
			///////////////////////////////

			//////////////////////////////////
			if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Left)
				{
					if (!isSwap && !isMoving) click++;
					pos = Mouse::getPosition(window) - offset;
				}
		}

		// mouse click
		if (click == 1)
		{
			x0 = pos.x / ts + 1;
			y0 = pos.y / ts + 1;
		}
		if (click == 2)
		{
			x = pos.x / ts + 1;
			y = pos.y / ts + 1;
			if (abs(x - x0) + abs(y - y0) == 1)
			{
				swap(grid[y0][x0], grid[y][x]); isSwap = 1; click = 0;
			}
			else click = 1;
		}

		//Match finding
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++)
			{
				if (grid[i][j].kind == grid[i + 1][j].kind)
					if (grid[i][j].kind == grid[i - 1][j].kind)
						for (int n = -1; n <= 1; n++) grid[i + n][j].match++;

				if (grid[i][j].kind == grid[i][j + 1].kind)
					if (grid[i][j].kind == grid[i][j - 1].kind)
						for (int n = -1; n <= 1; n++) grid[i][j + n].match++;
			}

		//Moving animation
		isMoving = false;
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++)
			{
				piece &p = grid[i][j];
				int dx, dy;
				for (int n = 0; n<4; n++)   // 4 - speed
				{
					dx = p.x - p.col*ts;
					dy = p.y - p.row*ts;
					if (dx) p.x -= dx / abs(dx);
					if (dy) p.y -= dy / abs(dy);
				}
				if (dx || dy) isMoving = 1;
			}

		//Deleting amimation
		if (!isMoving)
			for (int i = 1; i <= 8; i++)
				for (int j = 1; j <= 8; j++)
					if (grid[i][j].match) if (grid[i][j].alpha>10) { grid[i][j].alpha -= 10; isMoving = true; }

		//Get score
		int score = 0;
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++)
				score += grid[i][j].match;

		if (isSwap && !isMoving)
		{
			if (!score) swap(grid[y0][x0], grid[y][x]); isSwap = 0;

		}

		//Update grid
		if (!isMoving)
		{
			for (int i = 8; i>0; i--)
				for (int j = 1; j <= 8; j++)
					if (grid[i][j].match)
						for (int n = i; n>0; n--)
							if (!grid[n][j].match) { swap(grid[n][j], grid[i][j]); break; };

			for (int j = 1; j <= 8; j++)
				for (int i = 8, n = 0; i>0; i--)
					if (grid[i][j].match)
					{
						grid[i][j].kind = rand() % 7;
						grid[i][j].y = -ts*n++;
						grid[i][j].match = 0;
						grid[i][j].alpha = 255;
						och += 5;
						///std::cout <<score<<" "<<och<< std::endl;////////////

					}
		}


		//////draw///////
		window.draw(background);

		std::ostringstream ochString;    // объявили переменную
		ochString << och;		//занесли в нее число очков, то есть формируем строку
		text.setString("Кристали:");	//задаем строку тексту и вызываем сформированную выше строку методом .str() 
		text.setPosition(500, 385);
		window.draw(text);
		text1.setString(ochString.str());//задаем позицию текста, отступая от центра камеры
		text1.setPosition(650, 385);
		window.draw(text1);//рисую этот текст
		/////////////////////
		std::ostringstream gameTimeString;
		gameTimeString << gameTime;		//формируем строку
		text3.setString("Час iгри : " + gameTimeString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str()
		text3.setPosition(500, 350);//задаем позицию текста, отступая от центра камеры
		window.draw(text3);//рисую этот текст
		window.draw(text4);
		/////////////////////
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++)
			{
				piece p = grid[i][j];
				gems.setTextureRect(IntRect(p.kind * 49, 0, 49, 49));
				gems.setColor(Color(255, 255, 255, p.alpha));
				gems.setPosition(p.x, p.y);
				gems.move(offset.x - ts, offset.y - ts);

				window.draw(gems);
			}


		window.display();

	}

}
void gameRunning(RenderWindow & window){//ф-ция перезагружает игру , если это необходимо
	if (startGame(window)) { gameRunning(window); }////если startGame() == true, то вызываем занова ф-цию isGameRunning, которая в свою очередь опять вызывает startGame() 
}
////////////////////////////////////////////
int main()
{
	RenderWindow window(sf::VideoMode(740, 480), L"Кошелюк Максим - курсова робота");
	window.setFramerateLimit(60);

	gameRunning(window);//запускаем процесс игры

	return 0;
}
