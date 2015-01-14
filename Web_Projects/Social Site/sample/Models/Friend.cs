using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace sample.Models
{
    public class Friend
    {
        [Key]
        public int Id { get; set; }

        public int UserID { get; set; }
        public int FriendID { get; set; }
        public string UserUsername { get; set; }
        public string FriendUsername { get; set; }

        public bool Confirmed { get; set; }
        public bool reset { get; set; }
    }
}