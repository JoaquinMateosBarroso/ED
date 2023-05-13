/**
 * @file hash.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#pragma once
#include <cstddef> //for size_t
#include <cstdint> //for uint64_t
#include <memory>
#include <vector>
#include <random> //To generate random numbers.

/**
 * @brief Use this random bit generator to generate random numbers.
 * 
 */
extern std::minstd_rand Generator;

/**
 * @brief Generate an uniform random number in [0.0, 1.0) interval.
 * @return the random number.
 * @post ret_v in [0.0, 1.0)
 */
double uniform();

/**
 * @brief pick at random a value from the integer range [a, b].
 * @param a is lower bound of the range (inclusive).
 * @param b is upper bound of the range (exclusive).
 * @return the picked up value.
 * @prec a<b
 * @post ret_v in [a,b]
 */
std::uint64_t pick_at_random(std::uint64_t const& a, std::uint64_t const& b);

/**
 * @brief The Universal Hash function base class.
 * 
 * A universal hash function is one pick at at random from the universal family
 * H_p : {h(K) = ((a*K+b)%p)%m) }
 * where p is a prime number greater than the cardinality of the set of keys,
 * 0<a<p and 0<=b<p. The parameter m is the table size and it is normaly a two power.
 */
class UHash
{
public:

    /**
     * @brief A reference to a hash function.
     */
    typedef std::shared_ptr<UHash> Ref;
    /** @name Life cicle. */
    /** @{ */

    /**
     * @brief Create a hash function picked at random from Universal Family.     
     * @param m is the table size.
     * @param P is the P parameter.
     * @pre m is power of two greater than 1.
     * @pre P is a prime number greater than the cardinality of the keys set.
     */
    UHash(size_t m, std::uint64_t P=4294967311l);

    /**
     * @brief Create a hash function picked at random from Universal Family.
     * The p parameter used is 4294967311
     * @param m is the table size.
     * @param P is the P parameter.
     * @pre m is power of two greater than 1.
     * @pre P is a prime number greater than the cardinality of the keys set.
     */
    static Ref create(size_t m, std::uint64_t P=4294967311l);

    /**
     * @brief Create a universal hash function given all the parameters.
     * @param m is the table size.
     * @param p ,
     * @param a ,
     * @param b are the parameters of the Universal hash function.
     * @pre m is power of two greater than 1.
     * @pre m<p
     * @pre p is prime number.
     * @pre 1<=a<p
     * @pre 0<=b<p
     */
    UHash(size_t m, std::uint64_t p, std::uint64_t a, std::uint64_t b);

    /**
     * @brief Create a hash function.
     * @param m is the table size.
     * @param p ,
     * @param a ,
     * @param b are the parameters of the Universal hash function.
     * @pre m is power of two greater than 1.
     * @pre m<p
     * @pre p is prime number.
     * @pre 1<=a<p-1
     * @pre 0<=b<p-1
     */
    static Ref create(std::uint64_t m, std::uint64_t p, std::uint64_t a,
                      std::uint64_t b);
    /** @} */

    /** @name Observers. */
    /** @} */

    /**
     * @brief Create a new hash function pick up at random from de Universal
     *        Family.
     * @param m is the new table size.
     * @return a reference a to the new hash function.
     * @pre m is power of two greater than 1.
     */
    virtual Ref pick_at_new(std::uint64_t const& m) const;

    /**
     * @brief hash a key.
     * Hash the key to get a table index.
     * @param k is the key to be hashed.
     * @return the table index.
     * @pre k<p()
     * @post 0<=ret_v<m()
    */
    size_t operator()(std::uint64_t k) const;

    /**
     * @brief hash a key with collision resolution.
     * Hash the key to get a table index, giving alternatives for several probes.
     * @param k is the key to be hashed.
     * @param iter is the number of probes generates upto now.
     * @return the table index.
     * @pre k<p()
     * @post iter==0 implies ret_v is the universal hash function for integers.
     * @post iter>0 and ret_v is the next value of the collision resolution
     *       algorithm.
    */
    virtual size_t operator()(std::uint64_t k, size_t iter) const;

    /**
     * @brief the m parameter.
     */
    std::uint64_t m() const;    

    /**
     * @brief the m parameter.
     */
    std::uint64_t p() const;        
    
    /**
     * @brief the m parameter.
     */
    std::uint64_t a() const;    

    /**
     * @brief the m parameter.
     */
    std::uint64_t b() const;

    /** @} */
protected:

    // TODO: Give a representation 
    std::uint64_t m_;
    std::uint64_t p_;
    std::uint64_t a_;
    std::uint64_t b_;
    //
};

/**
 * @brief Base class for Open Addressing Collision Resolution algorithms. * 
 */
class OACollisionResolution
{
    public:

    /**
     * @brief A reference to a hash function.
     */
    typedef std::shared_ptr<OACollisionResolution> Ref;    

    /**
     * @brief hash a key with collision resolution.
     * Hash the key to get a table index, giving alternatives for several probes.
     * @param k is the key to be hashed.
     * @param iter is the number of probes generates upto now.
     * @return the table index.
     * @pre k<p()
     * @post iter==0 implies ret_v is the universal hash function for integers.
     * @post iter>0 and ret_v is the next value of the collision resolution
     *       algorithm.
    */
    virtual size_t operator()(std::uint64_t k, size_t iter) const = 0;


    /**
     * @brief Get a new version of the algorithm with a new table size choosing at random a new hash function.
     * @param new_m is the new table size.
     * @pre new_m is power of two greater than 1.
     * @return a new version of the algorithm.
     */
    virtual OACollisionResolution::Ref pick_at_new(std::uint64_t new_m) const = 0;

    /**
     * @brief Return the cardinality of the hash function.
     * 
     * @return the cardinality of the hash function.
     */
    virtual std::uint64_t m() const = 0;
};

/**
 * @brief Models an Universal Family hash function using
 *        linear probing to resolve collisions.
 */
class LPHash: public OACollisionResolution
{
public:

    /** @name Life cycle. */
    /** @{ */

    /**
     * @brief Create picked at random the hash from Universal Family.
     * @param hash_f is the universal hash function used.
     */
    LPHash(UHash::Ref hash_f);

    /**
     * @brief Create picked at random the hash from Universal Family.
     * @param hash_f is the universal hash function used.
     */
    static OACollisionResolution::Ref create(UHash::Ref hash_f);
       
    /** @} */

    /** @name Observers. */
    /** @} */
    
    size_t operator()(std::uint64_t k, size_t iter=0) const override;

    OACollisionResolution::Ref pick_at_new(std::uint64_t new_m) const override;

    std::uint64_t m() const override;

    /**
     * @brief Get the hash function used.
     * 
     * @return UHash::Ref to the hash function.
     */
    UHash::Ref hash() const;

    /** @} */
protected:

    UHash::Ref hash_f_;
};


/**
 * @brief Models an Universal Family hash function using
 *        quadratic probing to resolve collisions.
 *
 *        This function assume that the table size is two power and
 *        the parameters c1=c2=0.5
 */
class QPHash: public OACollisionResolution
{
public:

    /** @name Life cycle. */
    /** @{ */

    /**
     * @brief Create picked at random the hash from Universal Family.
     * @param hash_f is the universal hash function used.
     */
    QPHash(UHash::Ref hash_f);

    /**
     * @brief Create picked at random the hash from Universal Family.
     * @param hash_f is the universal hash function used.
     */
    static OACollisionResolution::Ref create(UHash::Ref hash_f);
       
    /** @} */

    /** @name Observers. */
    /** @} */
    
    size_t operator()(std::uint64_t k, size_t iter=0) const override;
    OACollisionResolution::Ref pick_at_new(std::uint64_t new_m) const override;
    std::uint64_t m() const override;

    /**
     * @brief Get the hash function used.
     * 
     * @return UHash::Ref to the hash function.
     */
    UHash::Ref hash() const;

    /** @} */
protected:
        
    UHash::Ref hash_f_;
};

/**
 * @brief Models an Universal Family hash function using  random probing to resolve collisions.
 * 
 * The c paremeter is set to (m/2)-1, so we assure c and m are prime relative.
 */
class RPHash: public OACollisionResolution
{
public:

    /** @name Life cycle. */
    /** @{ */
    /**
     * @brief Create picked at random the hash from Universal Family.
     * @param hash_f is the universal hash function used.
     * @param c is the random probing parameter.
     * @pre hash_f->m() and c are prime relative.
     */
    RPHash(UHash::Ref hash_f, std::uint64_t c);

    /**
     * @brief Create picked at random the hash from Universal Family.
     * @param hash_f is the universal hash function used.
     * @param c is the random probing parameter.
     * @pre hash_f->m() and c are prime relative.
     */
    static OACollisionResolution::Ref create(UHash::Ref hash_f, std::uint64_t c);
       
    /** @} */

    /** @name Observers. */
    /** @} */
    
    size_t operator()(std::uint64_t k, size_t iter=0) const override;
    OACollisionResolution::Ref pick_at_new(std::uint64_t new_m) const override;
    std::uint64_t m() const override;

    /**
     * @brief Get the hash function used.
     * 
     * @return UHash::Ref to the hash function.
     */
    UHash::Ref hash() const;

    /**
     * @brief Get the c parameter.
     * 
     * @return the c parameter.
     * @post ret_v and  hash()->m() are prime relative.
     */
    std::uint64_t c() const;

    /** @} */

protected:
        
    UHash::Ref hash_f_;
    std::uint64_t c_;
};

/**
 * @brief Models an Universal Family hash function using
 *        double hashing to resolve collisions.
 *
 */
class DHash: public OACollisionResolution
{
public:

    /** @name Life cycle. */
    /** @{ */
    /**
     * @brief Create picked at random the hash from Universal Family.
     * @param hash1 is a universal hash function used.
     * @param hash2 is another universal hash function from the same family of hash1.
     * @pre hash1->m()==hash2()->m()
     * @pre hash1->p()==hash2()->p()
     */
    DHash(UHash::Ref hash1, UHash::Ref hash2);

    /**
     * @brief Create picked at random the hash from Universal Family.
     * @param hash1 is a universal hash function used.
     * @param hash2 is another universal hash function from the same family of hash1.
     * @pre hash1->m()==hash2()->m()
     * @pre hash1->p()==hash2()->p()
     */
    static OACollisionResolution::Ref create(UHash::Ref hash1, UHash::Ref hash2);
       
    /** @} */

    /** @name Observers. */
    /** @} */
    
    size_t operator()(std::uint64_t k, size_t iter=0) const override;
    OACollisionResolution::Ref pick_at_new(std::uint64_t new_m) const override;
    std::uint64_t m() const override;

    /**
     * @brief Get the first hash function used.
     * 
     * @return UHash::Ref to the hash function.
     */
    UHash::Ref hash1() const;

    /**
     * @brief Get the second hash function used.
     * 
     * @return UHash::Ref to the hash function.
     */
    UHash::Ref hash2() const;

    /** @} */
protected:
        
    UHash::Ref hash1_;
    UHash::Ref hash2_;
};
