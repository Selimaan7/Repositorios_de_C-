#include <iostream>
#include <cstring>

using namespace std;

class TipoAlumno {
    private:
        virtual bool aprueba() const = 0;
        virtual const char* nombreTipo() const = 0;
        virtual void mostrarNotas() const = 0;
        virtual TipoAlumno* clonar() const = 0;
        virtual ~TipoAlumno() {}
};

class AlumnoInvitado : public TipoAlumno {
    private:
        float nota;

    public:
        AlumnoInvitado(float notaExamen = 0) : nota(notaExamen) {}
};