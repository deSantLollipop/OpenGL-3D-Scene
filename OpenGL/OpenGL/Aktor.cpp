#include "Aktor.h"

void Aktor::InicjujBuforWerteksów()
{
	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//Vertex Buffer Object (VBO)
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	Werteks* werteksy = NULL;
	liczbaWerteksów = TwórzTablicęWerteksów(werteksy);
	glBufferData(GL_ARRAY_BUFFER, liczbaWerteksów * sizeof(Werteks),
		werteksy, GL_STATIC_DRAW);
	delete[] werteksy;
}

void Aktor::Inicjuj(GLuint atrybutPołożenie, GLuint atrybutNormalna, GLuint atrybutKolor)
{
	InicjujBuforWerteksów();
	glVertexAttribPointer(atrybutPołożenie,
		Werteks::liczbaWspółrzędnychPołożenia,
		GL_FLOAT, GL_FALSE,
		Werteks::rozmiarWerteksu, 0);
	glEnableVertexAttribArray(atrybutPołożenie);
	glVertexAttribPointer(atrybutNormalna,
		Werteks::liczbaWspółrzędnychNormalnej,
		GL_FLOAT, GL_FALSE,
		Werteks::rozmiarWerteksu,
		(const GLvoid*)Werteks::rozmiarWektoraPołożenia);
	glEnableVertexAttribArray(atrybutNormalna);
	glVertexAttribPointer(atrybutKolor,
		Werteks::liczbaSkładowychKoloru,
		GL_FLOAT, GL_FALSE, Werteks::rozmiarWerteksu,
		(const GLvoid*)Werteks::rozmiarWektoraPołożenia);
	glEnableVertexAttribArray(atrybutKolor);
}

Aktor::Aktor()
	:liczbaWerteksów(-1), MacierzŚwiata(Macierz4::Jednostkowa)
{
}

void Aktor::UsuńBuforWerteksów()
{
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

Aktor::~Aktor()
{
	UsuńBuforWerteksów();
}

void Aktor::Rysuj() //default implementation for triangle strip
{
	assert(liczbaWerteksów > 0);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, liczbaWerteksów);
	//glBindBuffer(GL_ARRAY_BUFFER, NULL);
	//glBindVertexArray(NULL);
}

Kwadrat::Kwadrat(GLuint atrybutPołożenie, GLuint atrybutNormalna, GLuint atrybutKolor, float długośćKrawędzi)
	:Aktor(), długośćKrawędzi(długośćKrawędzi)
{
	Inicjuj(atrybutPołożenie, atrybutNormalna, atrybutKolor);
}

unsigned int Kwadrat::TwórzTablicęWerteksów(Werteks*& werteksy)
{
	const float x0 = długośćKrawędzi / 2.0f;
	const float y0 = długośćKrawędzi / 2.0f;
	werteksy = new Werteks[4];
	werteksy[0] = Werteks(-x0, -y0, 0.0f, 1, 1, 0, 1);
	//dolny lewy
	werteksy[1] = Werteks(x0, -y0, 0.0f, 1, 0, 1, 1);
	//dolny prawy
	werteksy[2] = Werteks(-x0, y0, 0.0f, 0, 1, 1, 1);
	//górny lewy
	werteksy[3] = Werteks(x0, y0, 0.0f, 1, 1, 1, 1);
	//górny prawy
	return 4;
}


Prostopadłościan::Prostopadłościan(GLuint atrybutPołożenie, GLuint atrybutNormalna,
	GLuint atrybutKolor, float długośćKrawędziX,
	float długośćKrawędziY, float długośćKrawędziZ, bool koloruj)
	:Aktor(), długośćKrawędziX(długośćKrawędziX),
	długośćKrawędziY(długośćKrawędziY),
	długośćKrawędziZ(długośćKrawędziZ), koloruj(koloruj)
{
	Inicjuj(atrybutPołożenie, atrybutNormalna,  atrybutKolor);
}

unsigned int Prostopadłościan::TwórzTablicęWerteksów(Werteks*& werteksy)
{
	const float x0 = długośćKrawędziX / 2.0f;
	const float y0 = długośćKrawędziY / 2.0f;
	const float z0 = długośćKrawędziZ / 2.0f;

	werteksy = new Werteks[24];

	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	if (koloruj) { r = 1.0f; g = 0.0f; b = 0.0f; }
	//tylna
	werteksy[0] = Werteks(x0, -y0, -z0, 0, 0, -1, r, g, b);
	werteksy[1] = Werteks(-x0, -y0, -z0, 0, 0, -1, r, g, b);
	werteksy[2] = Werteks(x0, y0, -z0, 0, 0, -1, r, g, b);
	werteksy[3] = Werteks(-x0, y0, -z0, 0, 0, -1, r, g, b);
	//przednia
	werteksy[4] = Werteks(-x0, -y0, z0, 0, 0, 1, r, g, b);
	werteksy[5] = Werteks(x0, -y0, z0, 0, 0, 1, r, g, b);
	werteksy[6] = Werteks(-x0, y0, z0, 0, 0, 1, r, g, b);
	werteksy[7] = Werteks(x0, y0, z0, 0, 0, 1, r, g, b);
	if (koloruj) { r = 0.0f; g = 1.0f; b = 0.0f; }
	//prawa
	werteksy[8] = Werteks(x0, -y0, z0, 1, 0, 0, r, g, b);
	werteksy[9] = Werteks(x0, -y0, -z0, 1, 0, 0, r, g, b);
	werteksy[10] = Werteks(x0, y0, z0, 1, 0, 0, r, g, b);
	werteksy[11] = Werteks(x0, y0, -z0, 1, 0, 0, r, g, b);
	//lewa
	werteksy[12] = Werteks(-x0, -y0, -z0, -1, 0, 0, r, g, b);
	werteksy[13] = Werteks(-x0, -y0, z0, -1, 0, 0, r, g, b);
	werteksy[14] = Werteks(-x0, y0, -z0, -1, 0, 0, r, g, b);
	werteksy[15] = Werteks(-x0, y0, z0, -1, 0, 0, r, g, b);
	if (koloruj) { r = 0.0f; g = 0.0f; b = 1.0f; }
	//górna
	werteksy[16] = Werteks(-x0, y0, z0, 0, 1, 0, r, g, b);
	werteksy[17] = Werteks(x0, y0, z0, 0, 1, 0, r, g, b);
	werteksy[18] = Werteks(-x0, y0, -z0, 0, 1, 0, r, g, b);
	werteksy[19] = Werteks(x0, y0, -z0, 0, 1, 0, r, g, b);
	//dolna
	werteksy[20] = Werteks(-x0, -y0, -z0, 0, -1, 0, r, g, b);
	werteksy[21] = Werteks(x0, -y0, -z0, 0, -1, 0, r, g, b);
	werteksy[22] = Werteks(-x0, -y0, z0, 0, -1, 0, r, g, b);
	werteksy[23] = Werteks(x0, -y0, z0, 0, -1, 0, r, g, b);
	return 24;
}

void Prostopadłościan::Rysuj()
{
	//bez bufora indeksów
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glMultiDrawArrays(GL_TRIANGLE_STRIP, pierwszeWerteksyPodciągów, liczbyWerteksówwPodciągach, 6);

	//glFrontFace(GL_CW);
	glCullFace(GL_FRONT);	
	//glEnable(GL_DEPTH_TEST);
	//glDisable(GL_DEPTH_TEST);
	
	//glBindBuffer(GL_ARRAY_BUFFER, NULL);
	//glBindVertexArray(NULL);
}

AktorZBuforemIndeksów::AktorZBuforemIndeksów()
	:Aktor(), liczbaIndeksów(-1)
{
}
AktorZBuforemIndeksów::~AktorZBuforemIndeksów()
{
	Aktor::~Aktor();
	UsuńBuforIndeksów();
}
void AktorZBuforemIndeksów::Inicjuj(GLuint atrybutPołożenie, GLuint atrybutNormalna, GLuint atrybutKolor)
{
	Aktor::Inicjuj(atrybutPołożenie, atrybutNormalna, atrybutKolor);
	InicjujBuforIndeksów();
}
void AktorZBuforemIndeksów::InicjujBuforIndeksów()
{
	glGenBuffers(1, &vbo_indeksy);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_indeksy);
	GLuint* indeksy = NULL;
	liczbaIndeksów = TwórzTablicęIndeksów(indeksy);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		liczbaIndeksów * sizeof(GLuint), indeksy, GL_STATIC_DRAW);
	delete[] indeksy;
}
void AktorZBuforemIndeksów::UsuńBuforIndeksów()
{
	glDeleteBuffers(1, &vbo_indeksy);
}
void AktorZBuforemIndeksów::Rysuj()
{
	assert(liczbaIndeksów > 0);
	//z buforem indeksów
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_indeksy);
	glDrawElements(GL_TRIANGLE_STRIP, liczbaIndeksów, GL_UNSIGNED_INT, 0);
	//glBindBuffer(GL_ARRAY_BUFFER, NULL);
	//glBindVertexArray(NULL);
}
