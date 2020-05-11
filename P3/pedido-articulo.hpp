#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP
#include "articulo.hpp"
#include "pedido.hpp"

class LineaPedido{
    public:
        explicit LineaPedido(double precio, unsigned cant=1) : preciovent_(precio), cantidad(cant_) {}
        double precio_venta() const{ return preciovent_; }
        unsigned cantidad() const{ return cant_; }

    private:
        double preciovent_;
        unsigned cant_;
};

struct OrdenaPedidos{
    bool operator()(const Pedido *ped1, const Pedido *ped2) const{
        return (ped1->numero() < ped2->numero());
    }
};

struct OrdenaArticulos{
    bool operator()(const Articulo *art1, const Articulo *art2) const{
        return (art1->referencia() < art2->referencia());
    }
};

class Pedido_Articulo{
    public:
        typedef std::map<Articulo *, LineaPedido, OrdenaArticulos> ItemsPedido;
        typedef std::map<Pedido *, LineaPedido, OrdenaPedidos> Pedidos;
        void pedir(Pedido &pedido, Articulo &articulo, double prec, unsigned cant=1);
        void pedir(Articulo &articulo, Pedido &pedido, double prec, unsigned cant=1);   //Sobrecarga
        
        ItemsPedido &detalle(Pedido &ped);
        Pedidos ventas(Articulo &art);
        std::ostream &mostrarDetallePedidos(std::ostream &);
        std::ostream &mostrarDetalleArticulos(std::ostream &);
        
    private:
        std::map<Pedido *, ItemsPedido, OrdenaPedidos> PA;
        std::map<Articulo *, Pedidos, OrdenaArticulos> AP;
};

std::ostream &operator<<(std::ostream &os, const LineaPedido &lp);
std::ostream &operator<<(std::ostream &os, const Pedido_Articulo::Pedidos &ped);
std::ostream &operator<<(std::ostream &os, const Pedido_Articulo::ItemsPedido &item);
#endif
