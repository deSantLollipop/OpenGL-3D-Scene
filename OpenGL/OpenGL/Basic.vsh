#version 330 core

layout(location = 0) in vec3 polozenie_in;
layout(location = 1) in vec3 normalna_in;
layout(location = 3) in vec4 kolor_in;

uniform bool UwzglednijKolorWerteksu = true;
uniform vec4 Kolor = vec4(1.0, 1.0, 0.0, 1.0);

const mat4 macierzJednostkowa = mat4(1.0);
uniform mat4 macierzSwiata = macierzJednostkowa;
uniform mat4 macierzWidoku = macierzJednostkowa;
uniform mat4 macierzRzutowania = macierzJednostkowa;
mat4 macierzMVP = macierzRzutowania * macierzWidoku*macierzSwiata;

//parametry zrodla swiatla
uniform vec4 Ca = vec4(1, 1, 1, 1);
uniform vec4 Cd = vec4(1, 1, 1, 1);
uniform vec4 Cs = vec4(1, 1, 1, 1);

uniform vec3 PolozenieZrodlaSwiatla = vec3(5, 2, 1);
uniform vec3 PolozenieKamery = vec3(0, 0, 1);


//parametry materialu
const float wa = 0.1;
const float wd = 1.0;
uniform vec4 Wa = vec4(wa, wa, wa, 1);
uniform vec4 Wd = vec4(wd, wd, wd, 1);
uniform vec4 Ws = vec4(0, 1, 0, 1);
uniform float WNs = 100.0;
mat3 macierzNormalnych = mat3(1.0);

vec4 ObliczKolorPhong(vec3 polozenie, vec3 normalna, vec4 kolor)
{
	vec3 R = polozenie;
	vec3 L = PolozenieZrodlaSwiatla - R;
	float odleglosc = length(L);
	L = normalize(L);
	vec3 N = normalize(normalna);
	float dotLN = dot(L, N);
	vec3 O = 2.0*dotLN*N - L; // reflect(-L,N);
	vec3 V = normalize(PolozenieKamery - R);
	float dotOVn = pow(max(dot(O, V), 0.0), WNs);
	dotLN = max(dotLN, 0.0);
	vec4 _kolor = Wa * Ca*kolor;
	_kolor += Wd * Cd*kolor*dotLN;
	_kolor += Ws * Cs*dotOVn;
	return _kolor;
}

out vec4 polozenie;
out vec4 kolor;

void main(void)
{
	polozenie = vec4(polozenie_in, 1.0);
	gl_Position = macierzMVP * polozenie;
	polozenie = macierzSwiata * polozenie;
	vec3 polozenie_scena = mat3(macierzSwiata)*polozenie_in;
	macierzNormalnych = transpose(inverse(mat3(macierzSwiata)));
	vec3 normalna_scena = macierzNormalnych * normalna_in;
	kolor = (UwzglednijKolorWerteksu) ? kolor_in : Kolor;
	kolor = ObliczKolorPhong(polozenie_scena,
		normalna_scena, kolor);
}
