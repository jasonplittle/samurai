#include "Character.hpp"


Character::Character(glm::vec2 initPosition, CharacterStats stats, CharacterStateMachine stateMachine, CharacterAnimator animator)
    : m_stats(stats), m_stateMachine(std::move(stateMachine)), m_animator(std::move(animator))
{
    m_body.Position = initPosition;
    m_body.Radii.y = m_stats.Height * 0.45f;
    m_body.Radii.x = m_stats.Width * 0.25f;
    m_body.UseGravity = true;
    m_body.Gravity = m_stats.Gravity;
}



void Character::Update(float dt)
{
    m_stateMachine.Update(*this, dt);
    m_animator.Update(dt);
}


// void Character::ChangeState(CharacterState newState)
// {
//     if (m_state == newState)
//         return;

//     OnExit(m_state);

//     m_state = newState;

//     OnEnter(m_state);
// }



// m_defendCooldownTimer += dt;

//     if (m_body.IsWalled && !m_body.IsGrounded)
//     {
//         m_state = CharacterState::WallContact;
//     }

//     switch(m_state)
//     {
//         case CharacterState::Idle:
//         {
//             // std::cout << "Idle" << std::endl;

//             if (std::abs(m_body.Velocity.x) > idleSpeed)
//             {
//                 m_state = CharacterState::Walk;
//             }

//             if (!m_body.IsGrounded)
//             {
//                 m_state = CharacterState::JumpMid;
//             }

//             break;
//         }
//         case CharacterState::Walk:
//         {
//             // std::cout << "Walk" << std::endl;

//             if (std::abs(m_body.Velocity.x) <= idleSpeed && !m_body.IsWalled)
//             {
//                 m_state = CharacterState::Idle;
//             }

//             if (!m_body.IsGrounded)
//             {
//                 m_state = CharacterState::JumpMid;
//             }

//             if (std::abs(m_body.Velocity.x) > walkSpeed)
//             {
//                 m_state = CharacterState::Run;
//             } 

//             break;
//         }
//         case CharacterState::Run:
//         {
//             if (!m_body.IsGrounded)
//             {
//                 m_state = CharacterState::JumpMid;
//             }

//             if (std::abs(m_body.Velocity.x) <= walkSpeed)
//             {
//                 m_state = CharacterState::Walk;
//             }

//             break;
//         }
//         case CharacterState::Attack1:
//         case CharacterState::Attack2:
//         case CharacterState::Attack3:
//         {
//             if (animationFinished)
//             {
//                 m_state = CharacterState::Idle;
//             }
//             break;
//         }
//         case CharacterState::Defend:
//         {
//             if (animationFinished)
//             {
//                 m_state = CharacterState::Idle;
//             }
//             break;
//         }
//         case CharacterState::JumpStart:
//         {
//             // std::cout << "Start" << std::endl;

//             if (m_body.Velocity.y < jumpMidThreshUp)
//             {
//                 m_state = CharacterState::JumpMid;
//             }

//             break;
//         }
//         case CharacterState::JumpMid:
//         {
//             // std::cout << "Mid" << std::endl;

//             if (m_body.Velocity.y < -jumpMidThreshDown && animationFinished) // Loop count at whole loop
//             {
//                 m_state = CharacterState::JumpFall;
//             }

//             if (m_body.IsGrounded && animationFinished)
//             {
//                 m_state = CharacterState::Idle;
//             }

//             break;
//         }
//         case CharacterState::JumpFall:
//         {
//             // std::cout << "Fall" << std::endl;
//             if (m_body.IsGrounded)
//             {
//                 m_state = CharacterState::Idle;
//                 m_body.Gravity = regGrav;
//             }

//             break;
//         }
//     }



// void Character::Jump()
// {
//     if (m_body.IsGrounded)
//     {
//         m_state = CharacterState::JumpStart;
//         m_body.Velocity.y = v0;
//     }
// }

// void Character::Attack()
// {
//     if (m_body.IsGrounded)
//     {
//         if (m_state != CharacterState::Attack2)
//         {
//             m_state = CharacterState::Attack1;
//         }
//         if (m_state == CharacterState::Attack1)
//         {
//             m_state = CharacterState::Attack2;
//         }
//         if (m_state == CharacterState::Attack2)
//         {
//             m_state = CharacterState::Attack3;
//         }
//     }
// }

// void Character::MoveDown()
// {
//     if (!m_body.IsGrounded)
//     {
//         m_state = CharacterState::JumpFall;
//         m_body.Gravity = fastGrav;
//     }
// }

// void Character::Defend()
// {
//     if (m_body.IsGrounded && m_defendCooldownTimer >= 1.0f)
//     {
//         m_state = CharacterState::Defend;
//         m_defendCooldownTimer = 0;

//         const float speedDif = -m_body.Velocity.x;
//         m_body.Acceleration.x = speedDif * defendDeccel;
//     }
// }

// void Character::MoveLeft() 
// { 
//     m_isFacingRight = false; 

//     const float speedDif = -runSpeed - m_body.Velocity.x;
//     m_body.Acceleration.x = speedDif * (m_state == CharacterState::Defend ? defendAccel : groundedAccel);
// };

// void Character::MoveRight() 
// { 
//     m_isFacingRight = true; 

//     const float speedDif = runSpeed - m_body.Velocity.x;
//     m_body.Acceleration.x = speedDif * (m_state == CharacterState::Defend ? defendAccel : groundedAccel);
// };

// void Character::Idle()
// {
//     const float speedDif = -m_body.Velocity.x;
//     m_body.Acceleration.x = speedDif * groundedDeccel;
// }