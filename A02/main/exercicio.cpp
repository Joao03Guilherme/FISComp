/*
Programa para fazer gráfico de um corpo sujeito a uma força de resistência do ar
*/  

const int MASSA = 1; // kg
const int GRAVIDADE = 10; // m/s^2
const double K = 1; // constante de resistência do ar

int main() {

    int dt = 0.01; // intervalo de tempo
    int t_max = 10; // tempo máximo


    return 0;
}





vector<double> resist_ar (vector<double> velocidade){
    vector<double> resistencia;
    for (int i = 0; i < velocidade.size(); i++){
        resistencia.push_back(K * velocidade[i] * velocidade[i]);
    }
    return resistencia;
}