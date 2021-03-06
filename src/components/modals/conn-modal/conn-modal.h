#ifndef COMPONENTS_MODALS_CONN_MODAL_CONN_MODAL_H
#define COMPONENTS_MODALS_CONN_MODAL_CONN_MODAL_H

/**
 * @brief Interfaccia ConnModal, modale per gestire errori di connessione
 * @file conn-modal.h
 */

namespace Modals {

    /** Modale che presenta gli errori in caso di malfunzionamento della connessione */
    namespace ConnModal {

       /**
        * Spazio dei nomi in cui vengono registrati gli eventi che vanno ad interagire
        * sulla finestra.
        */
        namespace Events {

            /** Metodo per mostrare il modale */
            void Show();

            /** Metodo per nascondere il modale */
            void Hide();

        }

        /** Metodo di inizializzazione del modale */
        void RegisterModal();

        /** Metodo di distruzione del modale */
        void EraseModal();
        
    }
}

#endif