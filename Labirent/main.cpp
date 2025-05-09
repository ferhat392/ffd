#include "Graf.h"

using namespace std;

int main() {
    Graf graf(25, 25);
    graf.labirentOku("labirent.txt");

    Node** bfsPath = nullptr;
    Node** dfsPath = nullptr;
    int bfsCost = 0, dfsCost = 0;
    int bfsAttemptCount = 0, dfsAttemptCount = 0;
    bool validPath = false;

    while (!validPath) {
        graf.setStartEndNode();

        bfsPath = new Node*[graf.rows * graf.cols];
        bfsCost = 0;
        bool bfsResult = BFS(graf, bfsPath, bfsCost, bfsAttemptCount);

        if (bfsResult && bfsCost <= 90) {
            validPath = true;
            cout << "BFS ile en kisa yol bulundu. Toplam maliyet: " << bfsCost << endl;
            cikisYolu(bfsPath, bfsCost + 1, "Sonuc_BFS.txt", bfsAttemptCount);
            cout << "Deneme sayisi: " << bfsAttemptCount << endl;
        } else {
            cout << "BFS ile maliyet 90'i asti." << endl;
        }
        delete[] bfsPath;

        dfsPath = new Node*[graf.rows * graf.cols];
        dfsCost = 0;
        bool dfsResult = DFS(graf, dfsPath, dfsCost, dfsAttemptCount);

        if (dfsResult && dfsCost <= 90) {
            validPath = true;
            cout << "DFS ile en kisa yol bulundu. Toplam maliyet: " << dfsCost << endl;
            cikisYolu(dfsPath, dfsCost + 1, "Sonuc_DFS.txt", dfsAttemptCount);
            cout << "Deneme sayisi: " << dfsAttemptCount << endl;
        } else {
            cout << "DFS ile maliyet 90'i asti." << endl;
        }
        delete[] dfsPath;
    }

    return 0;
}