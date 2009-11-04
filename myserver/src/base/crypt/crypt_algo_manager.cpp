/*
 MyServer
 Copyright (C) 2005-2009 Free Software Foundation, Inc.
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <include/base/crypt/crypt_algo_manager.h>
#include <memory>
#include <exception>

using namespace std;


/*!
 * C'tor.
 */
CryptAlgoManager::CryptAlgoManager ()
{

}


/*!
 * D'tor.
 */
CryptAlgoManager::~CryptAlgoManager ()
{

}

/*!
 * Register a new algorithm.
 * \param name Name of the algorithm.
 * \param bdr Builder function for the algorithm.
 */
void CryptAlgoManager::registerAlgorithm (string &name,
                                          CryptAlgoManager::builder bdr)
{
  algorithms.put (name, bdr);
}

/*!
 * Get a new instance for an algorithm class.
 * \param name The name of the algorithm.
 * \return A new instance on success.
 * \return NULL on failure.
 */
CryptAlgo *CryptAlgoManager::make (string &name)
{
  builder bdr = algorithms.get (name);
  if (bdr)
    return bdr ();

  return NULL;  
}

/* FIXME: Generalize.  */
class CryptAlgoManagerException : public exception
{
public:
  virtual const char *what () const throw ()
  {
    return message;
  }

  CryptAlgoManagerException (const char *message)
  {
    this->message = message;
  }

private:
  const char *message;
};

/*!
 * Check if F(value)=result, using the F specified by the algorithm.
 *
 * \param value The value to convert.
 * \param result The final result.
 * \param algo The name of the algorithm to use.
 * \return true if F(value)=result.
 * \throw If the algorithm is not registered, it throws an exception.
 */
bool CryptAlgoManager::check (string &value, string &result, string &algo)
{
  const size_t buffer_len = 256;
  char buffer[buffer_len];
  CryptAlgo *f = make (algo);
  if (!f)
    {
      snprintf (buffer, buffer_len, _("%s is not a registered algorithm"),
                algo.c_str ());
      throw CryptAlgoManagerException (buffer);
    }
  auto_ptr<CryptAlgo> keeper (f);
  f->init ();
  f->update (value.c_str (), value.length ());
  f->end (buffer);
  return !result.compare (buffer);
}