#include <assert.h>
#include <fstream>
#include "carregartextura.h"

using namespace std;

Textura::Textura(char* osPixelsDaImagem, int aLargura, int aAltura) : pixels(osPixelsDaImagem), largura(aLargura), altura(aAltura) {

}

Textura::~Textura() {
	delete[] pixels;
}

namespace {
    //Converter um vetor de 4 posições de char em um inteiro (ELDIAN FORM)
	int converterCharArrayEmInteiro(const char* bytes) {
		return (int)(((unsigned char)bytes[3] << 24) |
			((unsigned char)bytes[2] << 16) |
			((unsigned char)bytes[1] << 8) |
			(unsigned char)bytes[0]);
	}

    //Lendo 4 bytes como um inteiro (ELDIAN FORM)
	int lerOsBytesComoInteiro(ifstream &input) {
		char buffer[4];
		input.read(buffer, 4);
		return converterCharArrayEmInteiro(buffer);
	}


	//Auto_ptr(arrays)
	template<class T>
	class auto_array {
	private:
		T* array;
		mutable bool foiLiberado;
	public:
		explicit auto_array(T* array_ = NULL) :
			array(array_), foiLiberado(false) {
		}

		auto_array(const auto_array<T> &aarray) {
			array = aarray.array;
			foiLiberado = aarray.foiLiberado;
			aarray.foiLiberado = true;
		}

		~auto_array() {
			if (!foiLiberado && array != NULL) {
				delete[] array;
			}
		}

		T* get() const {
			return array;
		}

		T &operator*() const {
			return *array;
		}

		void operator=(const auto_array<T> &aarray) {
			if (!foiLiberado && array != NULL) {
				delete[] array;
			}
			array = aarray.array;
			foiLiberado = aarray.foiLiberado;
			aarray.foiLiberado = true;
		}

		T* operator->() const {
			return array;
		}

		T* release() {
			foiLiberado = true;
			return array;
		}

		void reset(T* array_ = NULL) {
			if (!foiLiberado && array != NULL) {
				delete[] array;
			}
			array = array_;
		}

		T* operator+(int i) {
			return array + i;
		}

		T &operator[](int i) {
			return array[i];
		}
	};
}

Textura* carregarImagemBMP(const char* filename) {
	ifstream entradaArquivo;
	entradaArquivo.open(filename, ifstream::binary);
	assert(!entradaArquivo.fail() || !"Could not find file");
	char buffer[2];
	entradaArquivo.read(buffer, 2);
	assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
	entradaArquivo.ignore(8);
	int infoForaDoConjunto = lerOsBytesComoInteiro(entradaArquivo); ///


    //Lendo informações da entrada
	int headerSize = lerOsBytesComoInteiro(entradaArquivo);
	int larguraDaImagem = lerOsBytesComoInteiro(entradaArquivo);
	int alturaDaImagem = lerOsBytesComoInteiro(entradaArquivo);


	//Lendo os dados obtidos
	int quantosBytesPorLinha = ((larguraDaImagem * 3 + 3) / 4) * 4 - (larguraDaImagem * 3 % 4);
	int tamanhoImagemCarregada = quantosBytesPorLinha * alturaDaImagem;
	auto_array<char> pixels(new char[tamanhoImagemCarregada]);
	entradaArquivo.seekg(infoForaDoConjunto, ios_base::beg);
	entradaArquivo.read(pixels.get(), tamanhoImagemCarregada);

	//Transformar a imagem na textura
	auto_array<char> pixels2(new char[larguraDaImagem * alturaDaImagem * 3]);
	for (int i = 0; i < alturaDaImagem; i++) {
		for (int j = 0; j < larguraDaImagem; j++) {
			for (int k = 0; k < 3; k++) {
				pixels2[3 * (larguraDaImagem * i + j) + k] =
					pixels[quantosBytesPorLinha * i + 3 * j + (2 - k)];
			}
		}
	}

	entradaArquivo.close();
	return new Textura(pixels2.release(), larguraDaImagem, alturaDaImagem);
}

