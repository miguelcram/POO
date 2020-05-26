#include "pedido-articulo.hpp"
#include <iomanip>

std::ostream &operator <<(std::ostream &os, const LineaPedido &lp){
    os << std::fixed << std::setprecision(2) << lp.precio_venta() << " €\t" << lp.cantidad();
    return os;
}

void Pedido_Articulo::pedir(Pedido &pedido, Articulo &articulo, double prec, unsigned cant){
    PA[&pedido].insert(std::make_pair(&articulo, LineaPedido(prec, cant)));
    AP[&articulo].insert(std::make_pair(&pedido, LineaPedido(prec, cant)));
}

void Pedido_Articulo::pedir(Articulo &articulo, Pedido &pedido, double prec, unsigned cant){
    Pedido_Articulo::pedir(pedido, articulo, prec, cant);
}

Pedido_Articulo::ItemsPedido &Pedido_Articulo::detalle(Pedido &ped){
    return PA[&ped];
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo &art){
    return AP[&art];
}

std::ostream &operator <<(std::ostream &os, const Pedido_Articulo::Pedidos &ped){
    unsigned tmp_cantidad = 0;
    double tmp_total = 0.0;

    os << "[Pedidos: " << ped.size() << "]\n"
       << Cadena(66, '=') << std::endl
       << " PVP\tCantidad\tFecha de venta\n"
       << Cadena(66, '=') << std::endl;

    for(const auto &i : ped){
        os << i.second << "\t\t" << i.first->fecha() << std::endl;
        tmp_total += i.second.precio_venta() * i.second.cantidad();
        tmp_cantidad += i.second.cantidad();
    }

    os << Cadena(66, '=') << std::endl
       << std::fixed << std::setprecision(2) << tmp_total << " €\t"
       << tmp_cantidad << std::endl;
    
    return os;
}

std::ostream &operator <<(std::ostream &os, const Pedido_Articulo::ItemsPedido &item){
    double tmp_total = 0.0;
    os << "\n"
       << Cadena(66, '=') << std::endl
       << " PVP\tCantidad\tArticulo\n"
       << Cadena(66, '=') << std::endl;

    for(const auto &i : item){
        os << i.second << "\t\t[" << i.first->referencia() << "] \""
           << i.first->titulo() << "\"" << std::endl;
        tmp_total += i.second.precio_venta() * i.second.cantidad();
    }

    os << Cadena(66, '=') << std::endl
       << "Total\t" << std::fixed << std::setprecision(2) << tmp_total << " €\n"
       << std::endl;
    
    return os;
}

std::ostream &Pedido_Articulo::mostrarDetallePedidos(std::ostream &os){
    double total = 0.0;

    for(const auto &i : PA){
        os << "Pedido num. " << i.first->numero()
           << "\nCliente: " << i.first->tarjeta()->titular()->nombre()
           << "\tFecha: " << i.first->fecha() << i.second;
        total += i.first->total();
    }

    return os << std::fixed << "\nTOTAL VENTAS:\t" << std::setprecision(2)
              << total << " €" << std::endl;
}

std::ostream &Pedido_Articulo::mostrarVentasArticulos(std::ostream &os){
    for(const auto &i:AP){
        os << "Ventas de [" << i.first->referencia() << "] \""
           << i.first->titulo() << "\"\n"
           << i.second << std::endl;
    }
    return os;
}
