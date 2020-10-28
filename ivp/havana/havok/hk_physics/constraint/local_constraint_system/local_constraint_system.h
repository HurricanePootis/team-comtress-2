#ifndef HK_PHYSICS_LOCAL_CONSTRAINT_SYSTEM_H
#define HK_PHYSICS_LOCAL_CONSTRAINT_SYSTEM_H

#include <hk_physics/constraint/local_constraint_system/local_constraint_system_bp.h>

// IVP_EXPORT_PUBLIC

struct penetratepair_t {
    short   obj0;
    short   obj1;
};

class hk_Local_Constraint_System : public hk_Link_EF
{
public:
    /// <summary>
    /// Creates a deactivated empty constraint system
    /// </summary>
    /// <param name="environment"></param>
    /// <param name="blueprint"></param>
    hk_Local_Constraint_System(hk_Environment*, hk_Local_Constraint_System_BP*);
    /// <summary>
    /// Activates the constraint system
    /// </summary>
    void activate(void);
    /// <summary>
    /// Deactivates the constraint system
    /// </summary>
    void deactivate(void);
    /// <summary>
    /// Deactivates the constraint silently
    /// </summary>
    void deactivate_silently(void);
    /// <summary>
    /// 
    /// </summary>
    virtual ~hk_Local_Constraint_System(void);
    /// <summary>
    /// Writes the current state of the constraint system
    /// </summary>
    /// <param name="pBluePrint">Blueprint to write the current constraint system state to</param>
    void write_to_blueprint(hk_Local_Constraint_System_BP*);
    /// <summary>
    /// 
    /// </summary>
    /// <param name="error_ticks"></param>
    inline void set_error_ticks(int error_ticks);
    /// <summary>
    /// 
    /// </summary>
    /// <param name="tolerance"></param>
    inline void set_error_tolerance(float tolerance);
    /// <summary>
    /// 
    /// </summary>
    /// <returns>true if constraint system is in an errored state</returns>
    inline bool has_error(void) const;
    /// <summary>
    /// 
    /// </summary>
    inline void clear_error(void);
    /// <summary>
    /// !INCOMPLETE! (crack) - I assume this is suppose to iterate against the current constrained rigid bodies, then
    /// send the possible collisions to the simunit to solve. The simunit will then respond back to the appropriate
    /// physics environment to fire events.
    /// </summary>
    /// <param name="pObject0"></param>
    /// <param name="pObject1"></param>
    void solve_penetration(IVP_Real_Object* pObject0, IVP_Real_Object* pObject1);
    /// <summary>
    /// 
    /// </summary>
    /// <param name="client_data"></param>
    inline void set_client_data(void* client_data);
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    inline void* get_client_data(void) const;
    /// <summary>
    /// 
    /// </summary>
    /// <returns>true if the constraint system is active</returns>
    inline bool is_active(void);
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    virtual const char* get_controller_name(void);
    /// <summary>
    /// 
    /// </summary>
    /// <param name="constraints_out"></param>
    void get_constraints_in_system(hk_Array<hk_Constraint*>& constraints_out);
    /// <summary>
    /// !UNIMPLEMENTED!
    /// </summary>
    /// <param name="pEnt"></param>
    virtual void entity_deletion_event(hk_Entity*);
    /// <summary>
    /// 
    /// </summary>
    /// <param name=""></param>
    void constraint_deletion_event(hk_Constraint*);
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    virtual hk_effector_priority get_effector_priority(void);
    /// <summary>
    /// 
    /// </summary>
    /// <param name="ent_out"></param>
    void get_effected_entities(hk_Array<hk_Entity*> &ent_out);
    /// <summary>
    /// 
    /// </summary>
    /// <param name="">pi</param>
    /// <param name="">ent_list</param>
    void apply_effector_PSI(hk_PSI_Info&, hk_Array<hk_Entity*>*);
    /// <summary>
    /// 
    /// </summary>
    /// <param name="pi"></param>
    /// <param name="ent_list"></param>
    void apply_effector_collision(hk_PSI_Info&, hk_Array<hk_Entity*>*);
    /// <summary>
    /// Get the epsilon which defines the softness of the constraint
    /// </summary>
    /// <returns></returns>
    hk_real get_epsilon(void);
    /// <summary>
    /// 
    /// </summary>
    /// <param name="errSq"></param>
    void report_square_error(float errSq);

protected:
    friend class hk_Constraint;

protected:
    /// <summary>
    /// Adds a constraint to the constraint system
    /// </summary>
    /// <param name=""></param>
    /// <param name="storage_size"></param>
    /// <remarks>if the constraint is deactivated, than adding constraints is much faster</remarks>
    void add_constraint(hk_Constraint*, int storage_size);
    /// <summary>
    /// 
    /// </summary>
    void recalc_storage_size(void);

protected:
    int m_n_iterations;
    int m_size_of_all_vmq_storages;

    hk_Array<hk_Constraint*> m_constraints;
    hk_Array<hk_Rigid_Body*> m_bodies;

    int m_minErrorTicks;
    int m_errorCount;
    int m_penetrationCount;

    penetratepair_t m_penetrationPairs[4];

    float m_errorTolerance;
    bool m_is_active;
    bool m_errorThisTick;
    bool m_needsSort;

    void * m_client_data;

//public:
//TODO(crack): See if a definition for this exists in the retail binaries.
//    virtual hk_real get_minimum_simulation_frequency(hk_Array<hk_Entity> *);
};

#include <hk_physics/constraint/local_constraint_system/local_constraint_system.inl>

#endif /* HK_PHYSICS_LOCAL_CONSTRAINT_SYSTEM_H */
