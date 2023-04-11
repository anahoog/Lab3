* Fifo circular para uso pelos novos componentes da libavr.

* UART com métodos put e get síncronos (sync_put() e sync_get(), por exemplo).

* UART com métodos put e get assíncronos (orientados a interrupções).

* UART com construtor que permite configurar a taxa de bits.
Obs.: as implementações de put e get assíncronos devem utilizar a Fifo circular para armazenamento de dados em trânsito.

