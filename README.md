Sterowanie programem następuje z pliku funkcji main w main.cpp 
<img width="966" height="360" alt="image" src="https://github.com/user-attachments/assets/6bfbcb7e-a4db-4fd3-aebd-7dd19e0c0fd4" />  
Aby symulacje generowały się poprawnie muszą zostać ustawione następujące zmienne:  
    const int num_simulations - liczba symulacji  
    constexpr int N - liczba węzłów w grafie
    constexpr double temperatureValues[] - wybrane wartości temperatury  
    constexpr int numByzantineValues[] -liczba węzłów bizantynskich  
    constexpr int maxSteps[] - liczba kroków w symulacji  
    constexpr double opinionsExpirations[]  - współczynnik wygasania opinii  
    BizStrategyKind kind - strategia węzłów bizantyńskich z 4 dostępnych:   
    BizStrategyKind::Random - strategia losowa  
    BizStrategyKind::Opposite - strategia negująca  
    BizStrategyKind::StickToStart - strategia statyczna  
    BizStrategyKind::Mix - startegia mieszana  
    Graphs::GraphType graphType - typ grafu z dwóch dostępnych:  
    Graphs::GraphType::Complete - graf pełny  
    Graphs::GraphType::Erdos_Renyi - graf Erdosa Renyiego   
  
  Proszę zwrócić uwagę, że w grafie Erdosa Renyiego można również ustawić prawdopodobieństwo połączenia między węzłami w linii 22 w pliku Graphs.cpp   
  <img width="441" height="267" alt="{294CEE38-78ED-4A9D-92A5-2B552B9C5D00}" src="https://github.com/user-attachments/assets/422c9c71-af0e-4886-abf6-bd5a4af747da" />

