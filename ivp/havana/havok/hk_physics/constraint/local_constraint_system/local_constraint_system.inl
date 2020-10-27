inline void hk_Local_Constraint_System::set_error_ticks(int error_ticks)
{ 
  m_minErrorTicks = error_ticks; 
}

inline void hk_Local_Constraint_System::set_error_tolerance(float tolerance)
{ 
  m_errorTolerance = tolerance; 
}

inline bool hk_Local_Constraint_System::has_error() const
{
  return m_errorCount > m_errorTolerance;
}

inline void hk_Local_Constraint_System::clear_error()
{
  m_errorCount = 0;
  m_errorThisTick = 0;
}

inline void hk_Local_Constraint_System::set_client_data(void* client_data)
{
  m_client_data = client_data;
}

inline void* hk_Local_Constraint_System::get_client_data() const
{
  return m_client_data;
}

inline bool hk_Local_Constraint_System::is_active()
{
  return m_is_active;
}
