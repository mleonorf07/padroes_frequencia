#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>

int main() {
    // 1. Carregar a imagem (coloca o nome de uma imagem real na mesma pasta do projeto)
    cv::Mat img = cv::imread("imagem.jpg");

    if (img.empty()) {
        std::cout << "Erro: Nao foi possivel carregar a imagem!" << std::endl;
        return -1;
    }

    // 2. Definir a paleta fixa de cores (em formato BGR: Azul, Verde, Vermelho)
    // Podes adicionar ou alterar as cores que quiseres aqui!
    std::vector<cv::Vec3b> palette = {
        { 0, 0, 0 },       // Preto
        { 255, 255, 255 }, // Branco
        { 255, 0, 0 },     // Azul puro
        { 0, 0, 255 },     // Vermelho puro
        { 0, 255, 0 }      // Verde puro
    };

    // 3. Percorrer cada linha e cada coluna (cada píxel) da imagem
    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            // Obter a referência para o píxel atual (canais BGR)
            cv::Vec3b& pixel = img.at<cv::Vec3b>(y, x);

            int bestIndex = 0;
            double minDistance = -1;

            // 4. Comparar o píxel com cada cor da paleta para encontrar a mais próxima
            for (size_t i = 0; i < palette.size(); i++) {
                // Cálculo da distância euclidiana entre as cores
                double b_diff = (double)pixel[0] - palette[i][0];
                double g_diff = (double)pixel[1] - palette[i][1];
                double r_diff = (double)pixel[2] - palette[i][2];
                double distance = std::sqrt(b_diff * b_diff + g_diff * g_diff + r_diff * r_diff);

                // Guardar a cor que tiver a menor distância
                if (minDistance == -1 || distance < minDistance) {
                    minDistance = distance;
                    bestIndex = i;
                }
            }

            // 5. Substituir a cor do píxel pela cor escolhida da paleta
            pixel = palette[bestIndex];
        }
    }

    // 6. Mostrar o resultado numa janela e guardar a imagem processada
    cv::imshow("Paleta Limitada - Ponto 1", img);
    cv::imwrite("resultado_ponto1.jpg", img);

    std::cout << "Processamento concluido com sucesso! Pressiona qualquer tecla para fechar." << std::endl;
    cv::waitKey(0); // Mantém a janela aberta até premir uma tecla

    return 0;
}