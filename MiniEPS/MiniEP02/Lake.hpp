#ifndef LAKE_HPP
#define LAKE_HPP

class Lake {
    public:
        vector<Amphibian> animals;
        int initial_free_rock;

    Lake (int n_toads, int n_frogs);

    bool sucess();
};

#endif
