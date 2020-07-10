#ifndef AKTOR_H
#define AKTOR_H

#include "MacierzGL.h"
#include "Werteks.h"

class Aktor
{
protected:
	unsigned int vao, vbo;
	unsigned int liczbaWerteksów;
private:
	void InicjujBuforWerteksów();
	void UsuńBuforWerteksów();
protected:
	virtual unsigned int TwórzTablicęWerteksów
	(Werteks*& werteksy) = 0;
public:
	Macierz4 MacierzŚwiata;
	virtual void Inicjuj(GLuint atrybutPołożenie, GLuint atrybutNormalna, GLuint atrybutKolor);
	virtual void Rysuj();
	Aktor();
	virtual ~Aktor();
};

class AktorZBuforemIndeksów : public Aktor
{
protected:
	unsigned int liczbaIndeksów;
	unsigned int vbo_indeksy;
private:
	void InicjujBuforIndeksów();
	void UsuńBuforIndeksów();
protected:
	virtual unsigned int TwórzTablicęIndeksów(GLuint*& indeksy) = 0;
public:
	virtual void Inicjuj(GLuint atrybutPołożenie /*= 0*/,
		GLuint atrybutNormalna,
		GLuint atrybutKolor /*= 3*/);
	virtual void Rysuj();
	AktorZBuforemIndeksów();
	virtual ~AktorZBuforemIndeksów();
};




class Kwadrat : public Aktor
{
private:
	float długośćKrawędzi;
	unsigned int TwórzTablicęWerteksów(Werteks*& werteksy);
public:
	Kwadrat(GLuint atrybutPołożenie, GLuint atrybutNormalna, GLuint atrybutKolor, float długośćKrawędzi = 2.0f);
};


class Prostopadłościan : public Aktor
{
private:
	float długośćKrawędziX, długośćKrawędziY, długośćKrawędziZ;
	bool koloruj;
	unsigned int TwórzTablicęWerteksów(Werteks*& werteksy);

	int pierwszeWerteksyPodciągów[6];
	int liczbyWerteksówwPodciągach[6];

public:
	void Rysuj();
	Prostopadłościan(GLuint atrybutPołożenie, GLuint atrybutNormalna,
		GLuint atrybutKolor, float długośćKrawędziX,
		float długośćKrawędziY, float długośćKrawędziZ,
		bool koloruj);
	static Prostopadłościan* StwórzSześcian(
		GLuint atrybutPołożenie, GLuint atrybutNormalna, GLuint atrybutKolor,
		float długośćKrawędzi, bool koloruj)
	{
		return new Prostopadłościan(
			atrybutPołożenie, atrybutNormalna, atrybutKolor,
			długośćKrawędzi, długośćKrawędzi, długośćKrawędzi,
			koloruj);
	}
};

#endif

