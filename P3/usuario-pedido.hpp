#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP
#include <set>
#include "pedido.hpp"

class Usuario_Pedido{
    public:
        typedef std::set<Pedido*> Pedidos;
        
        void asocia(Usuario &user, Pedido &ped){
            UP[&user].insert(&ped);
            PU[&ped] = &user;
        }
        
        void asocia(Pedido &ped, Usuario &user){
            asocia(user,ped);
        }
        
        Pedidos pedidos(Usuario &us) { return UP[&us]; }
        Usuario *cliente(Pedido &pedido) { return PU[&pedido]; }
    
    private:
        std::map<Pedido *, Usuario *> PU;
        std::map<Usuario *, Pedidos > UP;
};

#endif